#ifndef skynet_socket_server_h
#define skynet_socket_server_h

#define SOCKET_DATA 0
#define SOCKET_CLOSE 1
#define SOCKET_OPEN 2
#define SOCKET_ERROR 3
#define SOCKET_EXIT 4

struct socket_server;

union socket_message {
	struct {
		int id;
		int size;
		char * data;
	} data;
	struct {
		int id;
	} close;
	struct {
		int id;
		int session;
		int fd;
		char * addr;
	} open;
	struct {
		int id;
		int session;
	} error;
};

struct socket_server * socket_server_create();
void socket_server_release(struct socket_server *);
int socket_server_poll(struct socket_server *, union socket_message *result);

void socket_server_exit(struct socket_server *);

// return -1 when error
int socket_server_send(struct socket_server *, int id, const void * buffer, int sz);
void socket_server_close(struct socket_server *, int id);

// ctrl command below returns session
int socket_server_listen(struct socket_server *, const char * addr, int port, int backlog);
int socket_server_connect(struct socket_server *, const char * addr, int port);
int socket_server_bind(struct socket_server *, int fd);

#endif
