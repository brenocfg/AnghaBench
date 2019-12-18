#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct conn {int sock; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/ * ssl; int /*<<< orphan*/ * ssl_ctx; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_ERROR_SSL ; 
 int SSL_ERROR_SYSCALL ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_fd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 struct addrinfo* lookuphost (char const*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_read ; 
 int /*<<< orphan*/  ssl_write ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_read ; 
 int /*<<< orphan*/  tcp_write ; 

__attribute__((used)) static struct conn *connect_server(const char *hostname, in_port_t port,
                            bool nonblock, const bool ssl)
{
    struct conn *c;
    if (!(c = (struct conn *)calloc(1, sizeof(struct conn)))) {
        fprintf(stderr, "Failed to allocate the client connection: %s\n",
                strerror(errno));
        return NULL;
    }

    struct addrinfo *ai = lookuphost(hostname, port);
    int sock = -1;
    if (ai != NULL) {
       if ((sock = socket(ai->ai_family, ai->ai_socktype,
                          ai->ai_protocol)) != -1) {
          if (connect(sock, ai->ai_addr, ai->ai_addrlen) == -1) {
             fprintf(stderr, "Failed to connect socket: %s\n",
                     strerror(errno));
             close(sock);
             sock = -1;
          } else if (nonblock) {
              int flags = fcntl(sock, F_GETFL, 0);
              if (flags < 0 || fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0) {
                  fprintf(stderr, "Failed to enable nonblocking mode: %s\n",
                          strerror(errno));
                  close(sock);
                  sock = -1;
              }
          }
       } else {
          fprintf(stderr, "Failed to create socket: %s\n", strerror(errno));
       }

       freeaddrinfo(ai);
    }
    c->sock = sock;
#ifdef TLS
    if (sock > 0 && ssl) {
        c->ssl_ctx = SSL_CTX_new(SSLv23_client_method());
        if (c->ssl_ctx == NULL) {
            fprintf(stderr, "Failed to create the SSL context: %s\n",
                strerror(errno));
            close(sock);
            sock = -1;
        }
        c->ssl = SSL_new(c->ssl_ctx);
        if (c->ssl == NULL) {
            fprintf(stderr, "Failed to create the SSL object: %s\n",
                strerror(errno));
            close(sock);
            sock = -1;
        }
        SSL_set_fd (c->ssl, c->sock);
        int ret = SSL_connect(c->ssl);
        if (ret < 0) {
            int err = SSL_get_error(c->ssl, ret);
            if (err == SSL_ERROR_SYSCALL || err == SSL_ERROR_SSL) {
                fprintf(stderr, "SSL connection failed with error code : %s\n",
                    strerror(errno));
                close(sock);
                sock = -1;
            }
        }
        c->read = ssl_read;
        c->write = ssl_write;
    } else
#endif
    {
        c->read = tcp_read;
        c->write = tcp_write;
    }
    return c;
}