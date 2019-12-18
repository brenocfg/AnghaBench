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
struct net {int dummy; } ;
struct ctnl_timeout {int /*<<< orphan*/  timeout; int /*<<< orphan*/  head; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree_rcu (struct ctnl_timeout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_untimeout (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_head ; 
 scalar_t__ refcount_dec_if_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctnl_timeout_try_del(struct net *net, struct ctnl_timeout *timeout)
{
	int ret = 0;

	/* We want to avoid races with ctnl_timeout_put. So only when the
	 * current refcnt is 1, we decrease it to 0.
	 */
	if (refcount_dec_if_one(&timeout->refcnt)) {
		/* We are protected by nfnl mutex. */
		list_del_rcu(&timeout->head);
		nf_ct_untimeout(net, &timeout->timeout);
		kfree_rcu(timeout, rcu_head);
	} else {
		ret = -EBUSY;
	}
	return ret;
}