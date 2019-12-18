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
typedef  int /*<<< orphan*/  val ;
typedef  int uint16_t ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int dummy; } ;
struct nn_ctcp {int /*<<< orphan*/  ep; void* state; int /*<<< orphan*/  usock; int /*<<< orphan*/  retry; } ;
typedef  int /*<<< orphan*/  remote ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 void* NN_CTCP_STATE_CONNECTING ; 
 void* NN_CTCP_STATE_WAITING ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_RCVBUF ; 
 int /*<<< orphan*/  NN_SNDBUF ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_STAT_INPROGRESS_CONNECTIONS ; 
 int /*<<< orphan*/  NN_TCP ; 
 int /*<<< orphan*/  NN_TCP_NODELAY ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_backoff_start (int /*<<< orphan*/ *) ; 
 char* nn_ep_getaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ep_getopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_stat_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nn_iface_resolve (char const*,int,int,struct sockaddr_storage*,size_t*) ; 
 int nn_port_resolve (char const*,int) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_usock_bind (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  nn_usock_connect (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  nn_usock_setsockopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int nn_usock_start (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void nn_ctcp_start_connecting (struct nn_ctcp *self,
    struct sockaddr_storage *ss, size_t sslen)
{
    int rc;
    struct sockaddr_storage remote;
    size_t remotelen;
    struct sockaddr_storage local;
    size_t locallen;
    const char *addr;
    const char *end;
    const char *colon;
    const char *semicolon;
    uint16_t port;
    int ipv4only;
    size_t ipv4onlylen;
    int val;
    size_t sz;

    /*  Create IP address from the address string. */
    addr = nn_ep_getaddr (self->ep);
    memset (&remote, 0, sizeof (remote));

    /*  Parse the port. */
    end = addr + strlen (addr);
    colon = strrchr (addr, ':');
    rc = nn_port_resolve (colon + 1, end - colon - 1);
    errnum_assert (rc > 0, -rc);
    port = rc;

    /*  Check whether IPv6 is to be used. */
    ipv4onlylen = sizeof (ipv4only);
    nn_ep_getopt (self->ep, NN_SOL_SOCKET, NN_IPV4ONLY,
        &ipv4only, &ipv4onlylen);
    nn_assert (ipv4onlylen == sizeof (ipv4only));

    /*  Parse the local address, if any. */
    semicolon = strchr (addr, ';');
    memset (&local, 0, sizeof (local));
    if (semicolon)
        rc = nn_iface_resolve (addr, semicolon - addr, ipv4only,
            &local, &locallen);
    else
        rc = nn_iface_resolve ("*", 1, ipv4only, &local, &locallen);
    if (nn_slow (rc < 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CTCP_STATE_WAITING;
        return;
    }

    /*  Combine the remote address and the port. */
    remote = *ss;
    remotelen = sslen;
    if (remote.ss_family == AF_INET)
        ((struct sockaddr_in*) &remote)->sin_port = htons (port);
    else if (remote.ss_family == AF_INET6)
        ((struct sockaddr_in6*) &remote)->sin6_port = htons (port);
    else
        nn_assert (0);

    /*  Try to start the underlying socket. */
    rc = nn_usock_start (&self->usock, remote.ss_family, SOCK_STREAM, 0);
    if (nn_slow (rc < 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CTCP_STATE_WAITING;
        return;
    }

    /*  Set the relevant socket options. */
    sz = sizeof (val);
    nn_ep_getopt (self->ep, NN_SOL_SOCKET, NN_SNDBUF, &val, &sz);
    nn_assert (sz == sizeof (val));
    nn_usock_setsockopt (&self->usock, SOL_SOCKET, SO_SNDBUF,
        &val, sizeof (val));
    sz = sizeof (val);
    nn_ep_getopt (self->ep, NN_SOL_SOCKET, NN_RCVBUF, &val, &sz);
    nn_assert (sz == sizeof (val));
    nn_usock_setsockopt (&self->usock, SOL_SOCKET, SO_RCVBUF,
        &val, sizeof (val));
    sz = sizeof (val);
    nn_ep_getopt (self->ep, NN_TCP, NN_TCP_NODELAY, &val, &sz);
    nn_assert (sz == sizeof (val));
    nn_usock_setsockopt (&self->usock, IPPROTO_TCP, TCP_NODELAY,
        &val, sizeof (val));

    /*  Bind the socket to the local network interface. */
    rc = nn_usock_bind (&self->usock, (struct sockaddr*) &local, locallen);
    if (nn_slow (rc != 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CTCP_STATE_WAITING;
        return;
    }

    /*  Start connecting. */
    nn_usock_connect (&self->usock, (struct sockaddr*) &remote, remotelen);
    self->state = NN_CTCP_STATE_CONNECTING;
    nn_ep_stat_increment (self->ep, NN_STAT_INPROGRESS_CONNECTIONS, 1);
}