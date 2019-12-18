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
struct nn_bws {int /*<<< orphan*/  fsm; int /*<<< orphan*/  usock; int /*<<< orphan*/  awss; int /*<<< orphan*/ * aws; int /*<<< orphan*/  state; struct nn_ep* ep; } ;
typedef  int /*<<< orphan*/  ipv4only ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  NN_BWS_SRC_USOCK ; 
 int /*<<< orphan*/  NN_BWS_STATE_IDLE ; 
 int /*<<< orphan*/  NN_IPV4ONLY ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  alloc_assert (struct nn_bws*) ; 
 struct nn_bws* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_bws_ep_ops ; 
 int /*<<< orphan*/  nn_bws_handler ; 
 int nn_bws_listen (struct nn_bws*) ; 
 int /*<<< orphan*/  nn_bws_shutdown ; 
 char* nn_ep_getaddr (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getctx (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_ep_getopt (struct nn_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_ep_tran_setup (struct nn_ep*,int /*<<< orphan*/ *,struct nn_bws*) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int nn_iface_resolve (char const*,int,int,struct sockaddr_storage*,size_t*) ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 
 int nn_port_resolve (char const*,int) ; 
 int /*<<< orphan*/  nn_usock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

int nn_bws_create (struct nn_ep *ep)
{
    int rc;
    struct nn_bws *self;
    const char *addr;
    const char *end;
    const char *pos;
    struct sockaddr_storage ss;
    size_t sslen;
    int ipv4only;
    size_t ipv4onlylen;

    /*  Allocate the new endpoint object. */
    self = nn_alloc (sizeof (struct nn_bws), "bws");
    alloc_assert (self);
    self->ep = ep;

    nn_ep_tran_setup (ep, &nn_bws_ep_ops, self);
    addr = nn_ep_getaddr (ep);

    /*  Parse the port. */
    end = addr + strlen (addr);
    pos = strrchr (addr, ':');
    if (!pos) {
        return -EINVAL;
    }
    ++pos;
    rc = nn_port_resolve (pos, end - pos);
    if (rc < 0) {
        return -EINVAL;
    }

    /*  Check whether IPv6 is to be used. */
    ipv4onlylen = sizeof (ipv4only);
    nn_ep_getopt (ep, NN_SOL_SOCKET, NN_IPV4ONLY, &ipv4only, &ipv4onlylen);
    nn_assert (ipv4onlylen == sizeof (ipv4only));

    /*  Parse the address. */
    rc = nn_iface_resolve (addr, pos - addr - 1, ipv4only, &ss, &sslen);
    if (rc < 0) {
        return -ENODEV;
    }

    /*  Initialise the structure. */
    nn_fsm_init_root (&self->fsm, nn_bws_handler, nn_bws_shutdown,
        nn_ep_getctx (ep));
    self->state = NN_BWS_STATE_IDLE;
    self->aws = NULL;
    nn_list_init (&self->awss);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    nn_usock_init (&self->usock, NN_BWS_SRC_USOCK, &self->fsm);

    rc = nn_bws_listen (self);
    if (rc != 0) {
        return rc;
    }

    return 0;
}