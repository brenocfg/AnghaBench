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
struct nn_ep {int dummy; } ;
struct nn_btcp {int /*<<< orphan*/  listen_error; int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  atcps; int /*<<< orphan*/ * atcp; int /*<<< orphan*/  state; struct nn_ep* ep; } ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  NN_BTCP_SRC_BTCP ; 
 int /*<<< orphan*/  NN_BTCP_SRC_USOCK ; 
 int /*<<< orphan*/  NN_BTCP_STATE_IDLE ; 
 int /*<<< orphan*/  NN_BTCP_TYPE_LISTEN_ERR ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  alloc_assert (struct nn_btcp*) ; 
 struct nn_btcp* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_btcp_ep_ops ; 
 int /*<<< orphan*/  nn_btcp_handler ; 
 int nn_btcp_listen (struct nn_btcp*) ; 
 int /*<<< orphan*/  nn_btcp_shutdown ; 
 char* nn_ep_getaddr (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getopt (struct nn_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_btcp*) ; 
 int /*<<< orphan*/  nn_free (struct nn_btcp*) ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_raise_from_src (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int nn_iface_resolve (char const*,int,int,struct sockaddr_storage*,size_t*) ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 
 int nn_port_resolve (char const*,int) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_usock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

int nn_btcp_create (struct nn_ep *ep)
{
    int rc;
    struct nn_btcp *self;
    const char *addr;
    const char *end;
    const char *pos;
    struct sockaddr_storage ss;
    size_t sslen;
    int ipv4only;
    size_t ipv4onlylen;

    /*  Allocate the new endpoint object. */
    self = nn_alloc (sizeof (struct nn_btcp), "btcp");
    self->ep = ep;
    alloc_assert (self);

    nn_ep_tran_setup (ep, &nn_btcp_ep_ops, self);
    addr = nn_ep_getaddr (ep);

    /*  Parse the port. */
    end = addr + strlen (addr);
    pos = strrchr (addr, ':');
    if (pos == NULL) {
        nn_free (self);
        return -EINVAL;
    }
    ++pos;
    rc = nn_port_resolve (pos, end - pos);
    if (rc < 0) {
        nn_free (self);
        return -EINVAL;
    }

    /*  Check whether IPv6 is to be used. */
    ipv4onlylen = sizeof (ipv4only);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_IPV4ONLY, &ipv4only, &ipv4onlylen);
    nn_assert (ipv4onlylen == sizeof (ipv4only));

    /*  Parse the address. */
    rc = nn_iface_resolve (addr, pos - addr - 1, ipv4only, &ss, &sslen);
    if (nn_slow (rc < 0)) {
        nn_free (self);
        return -ENODEV;
    }

    /*  Initialise the structure. */
    nn_fsm_init_root (&self->fsm, nn_btcp_handler, nn_btcp_shutdown,
        nn_ep_getctx (ep));
    nn_fsm_event_init (&self->listen_error);
    self->state = NN_BTCP_STATE_IDLE;
    self->atcp = NULL;
    nn_list_init (&self->atcps);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    nn_usock_init (&self->usock, NN_BTCP_SRC_USOCK, &self->fsm);

    rc = nn_btcp_listen (self);
    if (rc != 0) {
        nn_fsm_raise_from_src (&self->fsm, &self->listen_error,
            NN_BTCP_SRC_BTCP, NN_BTCP_TYPE_LISTEN_ERR);
        return rc;
    }

    return 0;
}