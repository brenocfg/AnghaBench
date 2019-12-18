#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int sec_attr; int outbuffersz; int inbuffersz; } ;
struct nn_cipc {int /*<<< orphan*/  ep; int /*<<< orphan*/  state; TYPE_1__ usock; int /*<<< orphan*/  retry; } ;
typedef  int /*<<< orphan*/  ss ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  NN_CIPC_STATE_CONNECTING ; 
 int /*<<< orphan*/  NN_CIPC_STATE_WAITING ; 
 int /*<<< orphan*/  NN_IPC ; 
 int /*<<< orphan*/  NN_IPC_INBUFSZ ; 
 int /*<<< orphan*/  NN_IPC_OUTBUFSZ ; 
 int /*<<< orphan*/  NN_IPC_SEC_ATTR ; 
 int /*<<< orphan*/  NN_RCVBUF ; 
 int /*<<< orphan*/  NN_SNDBUF ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_STAT_INPROGRESS_CONNECTIONS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_backoff_start (int /*<<< orphan*/ *) ; 
 char* nn_ep_getaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ep_getopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_stat_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_usock_connect (TYPE_1__*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  nn_usock_setsockopt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int nn_usock_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void nn_cipc_start_connecting (struct nn_cipc *self)
{
    int rc;
    struct sockaddr_storage ss;
    struct sockaddr_un *un;
    const char *addr;
    int val;
    size_t sz;

    /*  Try to start the underlying socket. */
    rc = nn_usock_start (&self->usock, AF_UNIX, SOCK_STREAM, 0);
    if (nn_slow (rc < 0)) {
        nn_backoff_start (&self->retry);
        self->state = NN_CIPC_STATE_WAITING;
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

    /*  Create the IPC address from the address string. */
    addr = nn_ep_getaddr (self->ep);
    memset (&ss, 0, sizeof (ss));
    un = (struct sockaddr_un*) &ss;
    nn_assert (strlen (addr) < sizeof (un->sun_path));
    ss.ss_family = AF_UNIX;
    strncpy (un->sun_path, addr, sizeof (un->sun_path));

#if defined NN_HAVE_WINDOWS
    /* Get/Set security attribute pointer*/
    nn_ep_getopt (self->ep, NN_IPC, NN_IPC_SEC_ATTR, &self->usock.sec_attr, &sz);

    nn_ep_getopt (self->ep, NN_IPC, NN_IPC_OUTBUFSZ, &self->usock.outbuffersz, &sz);
    nn_ep_getopt (self->ep, NN_IPC, NN_IPC_INBUFSZ, &self->usock.inbuffersz, &sz);
#endif

    /*  Start connecting. */
    nn_usock_connect (&self->usock, (struct sockaddr*) &ss,
        sizeof (struct sockaddr_un));
    self->state  = NN_CIPC_STATE_CONNECTING;

    nn_ep_stat_increment (self->ep, NN_STAT_INPROGRESS_CONNECTIONS, 1);
}