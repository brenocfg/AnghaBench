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
typedef  scalar_t__ uint16_t ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int dummy; } ;
struct nn_btcp {int /*<<< orphan*/  usock; int /*<<< orphan*/  ep; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int /*<<< orphan*/  NN_BTCP_BACKLOG ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_btcp_start_accepting (struct nn_btcp*) ; 
 char* nn_ep_getaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ep_getopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int nn_iface_resolve (char const*,int,int,struct sockaddr_storage*,size_t*) ; 
 int nn_port_resolve (char const*,int) ; 
 int nn_usock_bind (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int nn_usock_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nn_usock_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_usock_stop (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int nn_btcp_listen (struct nn_btcp *self)
{
    int rc;
    struct sockaddr_storage ss;
    size_t sslen;
    int ipv4only;
    size_t ipv4onlylen;
    const char *addr;
    const char *end;
    const char *pos;
    uint16_t port;

    /*  First, resolve the IP address. */
    addr = nn_ep_getaddr (self->ep);
    memset (&ss, 0, sizeof (ss));

    /*  Parse the port. */
    end = addr + strlen (addr);
    pos = strrchr (addr, ':');
    if (pos == NULL) {
        return -EINVAL;
    }
    ++pos;
    rc = nn_port_resolve (pos, end - pos);
    if (rc <= 0)
        return rc;
    port = (uint16_t) rc;

    /*  Parse the address. */
    ipv4onlylen = sizeof (ipv4only);
    nn_ep_getopt (self->ep, NN_SOL_SOCKET, NN_IPV4ONLY,
        &ipv4only, &ipv4onlylen);
    nn_assert (ipv4onlylen == sizeof (ipv4only));
    rc = nn_iface_resolve (addr, pos - addr - 1, ipv4only, &ss, &sslen);
    if (rc < 0) {
        return rc;
    }

    /*  Combine the port and the address. */
    switch (ss.ss_family) {
    case AF_INET:
        ((struct sockaddr_in*) &ss)->sin_port = htons (port);
        sslen = sizeof (struct sockaddr_in);
        break;
    case AF_INET6:
        ((struct sockaddr_in6*) &ss)->sin6_port = htons (port);
        sslen = sizeof (struct sockaddr_in6);
        break;
    default:
        nn_assert (0);
    }

    /*  Start listening for incoming connections. */
    rc = nn_usock_start (&self->usock, ss.ss_family, SOCK_STREAM, 0);
    if (rc < 0) {
        return rc;
    }

    rc = nn_usock_bind (&self->usock, (struct sockaddr*) &ss, (size_t) sslen);
    if (rc < 0) {
       nn_usock_stop (&self->usock);
       return rc;
    }

    rc = nn_usock_listen (&self->usock, NN_BTCP_BACKLOG);
    if (rc < 0) {
        nn_usock_stop (&self->usock);
        return rc;
    }
    nn_btcp_start_accepting(self);

    return 0;
}