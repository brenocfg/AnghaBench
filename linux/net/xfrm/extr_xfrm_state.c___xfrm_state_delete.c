#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ spi; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  all; } ;
struct xfrm_state {int /*<<< orphan*/  byspi; TYPE_2__ id; int /*<<< orphan*/  bysrc; int /*<<< orphan*/  bydst; TYPE_1__ km; } ;
struct TYPE_6__ {int /*<<< orphan*/  xfrm_state_lock; int /*<<< orphan*/  state_num; } ;
struct net {TYPE_3__ xfrm; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_dev_state_delete (struct xfrm_state*) ; 
 int /*<<< orphan*/  xfrm_state_put (struct xfrm_state*) ; 
 struct net* xs_net (struct xfrm_state*) ; 

int __xfrm_state_delete(struct xfrm_state *x)
{
	struct net *net = xs_net(x);
	int err = -ESRCH;

	if (x->km.state != XFRM_STATE_DEAD) {
		x->km.state = XFRM_STATE_DEAD;
		spin_lock(&net->xfrm.xfrm_state_lock);
		list_del(&x->km.all);
		hlist_del_rcu(&x->bydst);
		hlist_del_rcu(&x->bysrc);
		if (x->id.spi)
			hlist_del_rcu(&x->byspi);
		net->xfrm.state_num--;
		spin_unlock(&net->xfrm.xfrm_state_lock);

		xfrm_dev_state_delete(x);

		/* All xfrm_state objects are created by xfrm_state_alloc.
		 * The xfrm_state_alloc call gives a reference, and that
		 * is what we are dropping here.
		 */
		xfrm_state_put(x);
		err = 0;
	}

	return err;
}