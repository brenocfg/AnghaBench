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
struct nf_acct {int /*<<< orphan*/  head; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree_rcu (struct nf_acct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_head ; 
 scalar_t__ refcount_dec_if_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfnl_acct_try_del(struct nf_acct *cur)
{
	int ret = 0;

	/* We want to avoid races with nfnl_acct_put. So only when the current
	 * refcnt is 1, we decrease it to 0.
	 */
	if (refcount_dec_if_one(&cur->refcnt)) {
		/* We are protected by nfnl mutex. */
		list_del_rcu(&cur->head);
		kfree_rcu(cur, rcu_head);
	} else {
		ret = -EBUSY;
	}
	return ret;
}