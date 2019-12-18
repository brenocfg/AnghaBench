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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sadr ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
 int AF_LOCAL ; 
#define  AF_UNIX 128 
 int /*<<< orphan*/  D_LISTENER ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int accept4 (int,struct sockaddr*,int*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connection_allowed (int,char*,char*,size_t,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ getnameinfo (struct sockaddr*,int,char*,int,char*,int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strncpyz (char*,char*,size_t) ; 

int accept_socket(int fd, int flags, char *client_ip, size_t ipsize, char *client_port, size_t portsize,
                  char *client_host, size_t hostsize, SIMPLE_PATTERN *access_list, int allow_dns) {
    struct sockaddr_storage sadr;
    socklen_t addrlen = sizeof(sadr);

    int nfd = accept4(fd, (struct sockaddr *)&sadr, &addrlen, flags);
    if (likely(nfd >= 0)) {
        if (getnameinfo((struct sockaddr *)&sadr, addrlen, client_ip, (socklen_t)ipsize,
                        client_port, (socklen_t)portsize, NI_NUMERICHOST | NI_NUMERICSERV) != 0) {
            error("LISTENER: cannot getnameinfo() on received client connection.");
            strncpyz(client_ip, "UNKNOWN", ipsize - 1);
            strncpyz(client_port, "UNKNOWN", portsize - 1);
        }
        if (!strcmp(client_ip, "127.0.0.1") || !strcmp(client_ip, "::1")) {
            strncpy(client_ip, "localhost", ipsize);
            client_ip[ipsize - 1] = '\0';
        }

#ifdef __FreeBSD__
        if(((struct sockaddr *)&sadr)->sa_family == AF_LOCAL)
            strncpyz(client_ip, "localhost", ipsize);
#endif

        client_ip[ipsize - 1] = '\0';
        client_port[portsize - 1] = '\0';

        switch (((struct sockaddr *)&sadr)->sa_family) {
            case AF_UNIX:
                debug(D_LISTENER, "New UNIX domain web client from %s on socket %d.", client_ip, fd);
                // set the port - certain versions of libc return garbage on unix sockets
                strncpy(client_port, "UNIX", portsize);
                client_port[portsize - 1] = '\0';
                break;

            case AF_INET:
                debug(D_LISTENER, "New IPv4 web client from %s port %s on socket %d.", client_ip, client_port, fd);
                break;

            case AF_INET6:
                if (strncmp(client_ip, "::ffff:", 7) == 0) {
                    memmove(client_ip, &client_ip[7], strlen(&client_ip[7]) + 1);
                    debug(D_LISTENER, "New IPv4 web client from %s port %s on socket %d.", client_ip, client_port, fd);
                }
                else
                    debug(D_LISTENER, "New IPv6 web client from %s port %s on socket %d.", client_ip, client_port, fd);
                break;

            default:
                debug(D_LISTENER, "New UNKNOWN web client from %s port %s on socket %d.", client_ip, client_port, fd);
                break;
        }
        if (!connection_allowed(nfd, client_ip, client_host, hostsize, access_list, "connection", allow_dns)) {
            errno = 0;
            error("Permission denied for client '%s', port '%s'", client_ip, client_port);
            close(nfd);
            nfd = -1;
            errno = EPERM;
        }
    }
#ifdef HAVE_ACCEPT4
    else if (errno == ENOSYS)
        error("netdata has been compiled with the assumption that the system has the accept4() call, but it is not here. Recompile netdata like this: ./configure --disable-accept4 ...");
#endif

    return nfd;
}