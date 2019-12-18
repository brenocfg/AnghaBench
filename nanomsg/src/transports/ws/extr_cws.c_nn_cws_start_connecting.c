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
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int dummy; } ;
struct nn_cws {int /*<<< orphan*/  ep; void* state; int /*<<< orphan*/  usock; int /*<<< orphan*/  retry; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  nic; } ;
typedef  int /*<<< orphan*/  remote ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 void* NN_CWS_STATE_CONNECTING ; 
 void* NN_CWS_STATE_WAITING ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_RCVBUF ; 
 int /*<<< orphan*/  NN_SNDBUF ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_STAT_INPROGRESS_CONNECTIONS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_backoff_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_chunkref_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_chunkref_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ep_getopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_stat_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nn_iface_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sockaddr_storage*,size_t*) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_usock_bind (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  nn_usock_connect (int /*<<< orphan*/ *,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  nn_usock_setsockopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int nn_usock_start (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nn_cws_start_connecting (struct nn_cws *self,
    struct sockaddr_storage *ss, size_t sslen)
{
    int rc;
    struct sockaddr_storage remote;
    size_t remotelen;
    struct sockaddr_storage local;
    size_t locallen;
    int ipv4only;
    int val;
    size_t sz;

    memset (&remote, 0, sizeof (remote));
    memset (&local, 0, sizeof (local));

    /*  Check whether IPv6 is to be used. */
    sz = sizeof (ipv4only);
    nn_ep_getopt (self->ep, NN_SOL_SOCKET, NN_IPV4ONLY, &ipv4only, &sz);
    nn_assert (sz == sizeof (ipv4only));

    rc = nn_iface_resolve (nn_chunkref_data (&self->nic),
    nn_chunkref_size (&self->nic), ipv4only, &local, &locallen);

    if (nn_slow (rc < 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CWS_STATE_WAITING;
        return;
    }

    /*  Combine the remote address and the port. */
    remote = *ss;
    remotelen = sslen;
    if (remote.ss_family == AF_INET)
        ((struct sockaddr_in*) &remote)->sin_port = htons (self->remote_port);
    else if (remote.ss_family == AF_INET6)
        ((struct sockaddr_in6*) &remote)->sin6_port = htons (self->remote_port);
    else
        nn_assert (0);

    /*  Try to start the underlying socket. */
    rc = nn_usock_start (&self->usock, remote.ss_family, SOCK_STREAM, 0);
    if (nn_slow (rc < 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CWS_STATE_WAITING;
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

    /*  Bind the socket to the local network interface. */
    rc = nn_usock_bind (&self->usock, (struct sockaddr*) &local, locallen);
    if (nn_slow (rc != 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CWS_STATE_WAITING;
        return;
    }

    /*  Start connecting. */
    nn_usock_connect (&self->usock, (struct sockaddr*) &remote, remotelen);
    self->state = NN_CWS_STATE_CONNECTING;
    nn_ep_stat_increment (self->ep, NN_STAT_INPROGRESS_CONNECTIONS, 1);
}