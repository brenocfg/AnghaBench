#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct timeval {int dummy; } ;
struct sockaddr_in6 {scalar_t__ sin6_scope_id; int /*<<< orphan*/  sin6_flowinfo; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; } ;
struct addrinfo {int ai_family; int ai_socktype; int ai_protocol; scalar_t__ ai_addrlen; TYPE_1__* ai_addr; scalar_t__ ai_flags; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  servBfr ;
typedef  int /*<<< orphan*/  hostBfr ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_3__ {int sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  D_CONNECT_TO ; 
 scalar_t__ EALREADY ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 int PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  getnameinfo (TYPE_1__*,scalar_t__,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  info (char*,char*,char*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int,int,int) ; 

__attribute__((used)) static inline int connect_to_this_ip46(int protocol, int socktype, const char *host, uint32_t scope_id, const char *service, struct timeval *timeout) {
    struct addrinfo hints;
    struct addrinfo *ai_head = NULL, *ai = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = PF_UNSPEC;   /* Allow IPv4 or IPv6 */
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;

    int ai_err = getaddrinfo(host, service, &hints, &ai_head);
    if (ai_err != 0) {
        error("Cannot resolve host '%s', port '%s': %s", host, service, gai_strerror(ai_err));
        return -1;
    }

    int fd = -1;
    for (ai = ai_head; ai != NULL && fd == -1; ai = ai->ai_next) {

        if (ai->ai_family == PF_INET6) {
            struct sockaddr_in6 *pSadrIn6 = (struct sockaddr_in6 *) ai->ai_addr;
            if(pSadrIn6->sin6_scope_id == 0) {
                pSadrIn6->sin6_scope_id = scope_id;
            }
        }

        char hostBfr[NI_MAXHOST + 1];
        char servBfr[NI_MAXSERV + 1];

        getnameinfo(ai->ai_addr,
                    ai->ai_addrlen,
                    hostBfr,
                    sizeof(hostBfr),
                    servBfr,
                    sizeof(servBfr),
                    NI_NUMERICHOST | NI_NUMERICSERV);

        debug(D_CONNECT_TO, "Address info: host = '%s', service = '%s', ai_flags = 0x%02X, ai_family = %d (PF_INET = %d, PF_INET6 = %d), ai_socktype = %d (SOCK_STREAM = %d, SOCK_DGRAM = %d), ai_protocol = %d (IPPROTO_TCP = %d, IPPROTO_UDP = %d), ai_addrlen = %lu (sockaddr_in = %lu, sockaddr_in6 = %lu)",
              hostBfr,
              servBfr,
              (unsigned int)ai->ai_flags,
              ai->ai_family,
              PF_INET,
              PF_INET6,
              ai->ai_socktype,
              SOCK_STREAM,
              SOCK_DGRAM,
              ai->ai_protocol,
              IPPROTO_TCP,
              IPPROTO_UDP,
              (unsigned long)ai->ai_addrlen,
              (unsigned long)sizeof(struct sockaddr_in),
              (unsigned long)sizeof(struct sockaddr_in6));

        switch (ai->ai_addr->sa_family) {
            case PF_INET: {
                struct sockaddr_in *pSadrIn = (struct sockaddr_in *)ai->ai_addr;
                (void)pSadrIn;

                debug(D_CONNECT_TO, "ai_addr = sin_family: %d (AF_INET = %d, AF_INET6 = %d), sin_addr: '%s', sin_port: '%s'",
                      pSadrIn->sin_family,
                      AF_INET,
                      AF_INET6,
                      hostBfr,
                      servBfr);
                break;
            }

            case PF_INET6: {
                struct sockaddr_in6 *pSadrIn6 = (struct sockaddr_in6 *) ai->ai_addr;
                (void)pSadrIn6;

                debug(D_CONNECT_TO,"ai_addr = sin6_family: %d (AF_INET = %d, AF_INET6 = %d), sin6_addr: '%s', sin6_port: '%s', sin6_flowinfo: %u, sin6_scope_id: %u",
                      pSadrIn6->sin6_family,
                      AF_INET,
                      AF_INET6,
                      hostBfr,
                      servBfr,
                      pSadrIn6->sin6_flowinfo,
                      pSadrIn6->sin6_scope_id);
                break;
            }

            default: {
                debug(D_CONNECT_TO, "Unknown protocol family %d.", ai->ai_family);
                continue;
            }
        }

        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if(fd != -1) {
            if(timeout) {
                if(setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (char *) timeout, sizeof(struct timeval)) < 0)
                    error("Failed to set timeout on the socket to ip '%s' port '%s'", hostBfr, servBfr);
            }

            errno = 0;
            if(connect(fd, ai->ai_addr, ai->ai_addrlen) < 0) {
                if(errno == EALREADY || errno == EINPROGRESS) {
                    info("Waiting for connection to ip %s port %s to be established", hostBfr, servBfr);

                    fd_set fds;
                    FD_ZERO(&fds);
                    FD_SET(0, &fds);
                    int rc = select (1, NULL, &fds, NULL, timeout);

                    if(rc > 0 && FD_ISSET(fd, &fds)) {
                        info("connect() to ip %s port %s completed successfully", hostBfr, servBfr);
                    }
                    else if(rc == -1) {
                        error("Failed to connect to '%s', port '%s'. select() returned %d", hostBfr, servBfr, rc);
                        close(fd);
                        fd = -1;
                    }
                    else {
                        error("Timed out while connecting to '%s', port '%s'. select() returned %d", hostBfr, servBfr, rc);
                        close(fd);
                        fd = -1;
                    }
                }
                else {
                    error("Failed to connect to '%s', port '%s'", hostBfr, servBfr);
                    close(fd);
                    fd = -1;
                }
            }

            if(fd != -1)
                debug(D_CONNECT_TO, "Connected to '%s' on port '%s'.", hostBfr, servBfr);
        }
    }

    freeaddrinfo(ai_head);

    return fd;
}