#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  all; } ;
struct xfrm_policy {TYPE_2__ walk; int /*<<< orphan*/  byidx; int /*<<< orphan*/  bydst_inexact_list; int /*<<< orphan*/  bydst; } ;
struct TYPE_3__ {int /*<<< orphan*/ * policy_count; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static struct xfrm_policy *__xfrm_policy_unlink(struct xfrm_policy *pol,
						int dir)
{
	struct net *net = xp_net(pol);

	if (list_empty(&pol->walk.all))
		return NULL;

	/* Socket policies are not hashed. */
	if (!hlist_unhashed(&pol->bydst)) {
		hlist_del_rcu(&pol->bydst);
		hlist_del_init(&pol->bydst_inexact_list);
		hlist_del(&pol->byidx);
	}

	list_del_init(&pol->walk.all);
	net->xfrm.policy_count[dir]--;

	return pol;
}