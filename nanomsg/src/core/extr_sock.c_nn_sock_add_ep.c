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
struct nn_transport {int dummy; } ;
struct nn_sock {int eid; int /*<<< orphan*/  ctx; int /*<<< orphan*/  eps; } ;
struct nn_ep {int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SOCK_SRC_EP ; 
 struct nn_ep* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_ctx_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ctx_leave (int /*<<< orphan*/ *) ; 
 int nn_ep_init (struct nn_ep*,int /*<<< orphan*/ ,struct nn_sock*,int,struct nn_transport const*,int,char const*) ; 
 int /*<<< orphan*/  nn_ep_start (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_free (struct nn_ep*) ; 
 int /*<<< orphan*/  nn_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 

int nn_sock_add_ep (struct nn_sock *self, const struct nn_transport *transport,
    int bind, const char *addr)
{
    int rc;
    struct nn_ep *ep;
    int eid;

    nn_ctx_enter (&self->ctx);

    /*  Instantiate the endpoint. */
    ep = nn_alloc (sizeof (struct nn_ep), "endpoint");
    rc = nn_ep_init (ep, NN_SOCK_SRC_EP, self, self->eid, transport,
        bind, addr);
    if (nn_slow (rc < 0)) {
        nn_free (ep);
        nn_ctx_leave (&self->ctx);
        return rc;
    }
    nn_ep_start (ep);

    /*  Increase the endpoint ID for the next endpoint. */
    eid = self->eid;
    ++self->eid;

    /*  Add it to the list of active endpoints. */
    nn_list_insert (&self->eps, &ep->item, nn_list_end (&self->eps));

    nn_ctx_leave (&self->ctx);

    return eid;
}