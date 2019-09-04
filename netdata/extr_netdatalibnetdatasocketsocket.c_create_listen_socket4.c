#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char* uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  D_LISTENER ; 
 int SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char*,int) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 int /*<<< orphan*/  htons (char*) ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,void*) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_enlarge_in (int) ; 
 int /*<<< orphan*/  sock_setnonblock (int) ; 
 int /*<<< orphan*/  sock_setreuse (int,int) ; 
 int /*<<< orphan*/  sock_setreuse_port (int,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int create_listen_socket4(int socktype, const char *ip, uint16_t port, int listen_backlog) {
    int sock;

    debug(D_LISTENER, "LISTENER: IPv4 creating new listening socket on ip '%s' port %d, socktype %d", ip, port, socktype);

    sock = socket(AF_INET, socktype, 0);
    if(sock < 0) {
        error("LISTENER: IPv4 socket() on ip '%s' port %d, socktype %d failed.", ip, port, socktype);
        return -1;
    }

    sock_setreuse(sock, 1);
    sock_setreuse_port(sock, 1);
    sock_setnonblock(sock);
    sock_enlarge_in(sock);

    struct sockaddr_in name;
    memset(&name, 0, sizeof(struct sockaddr_in));
    name.sin_family = AF_INET;
    name.sin_port = htons (port);

    int ret = inet_pton(AF_INET, ip, (void *)&name.sin_addr.s_addr);
    if(ret != 1) {
        error("LISTENER: Failed to convert IP '%s' to a valid IPv4 address.", ip);
        close(sock);
        return -1;
    }

    if(bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0) {
        close(sock);
        error("LISTENER: IPv4 bind() on ip '%s' port %d, socktype %d failed.", ip, port, socktype);
        return -1;
    }

    if(socktype == SOCK_STREAM && listen(sock, listen_backlog) < 0) {
        close(sock);
        error("LISTENER: IPv4 listen() on ip '%s' port %d, socktype %d failed.", ip, port, socktype);
        return -1;
    }

    debug(D_LISTENER, "LISTENER: Listening on IPv4 ip '%s' port %d, socktype %d", ip, port, socktype);
    return sock;
}