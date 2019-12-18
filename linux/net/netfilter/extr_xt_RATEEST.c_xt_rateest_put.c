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
struct xt_rateest_net {int /*<<< orphan*/  hash_lock; } ;
struct xt_rateest {scalar_t__ refcnt; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  list; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct xt_rateest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct xt_rateest_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  xt_rateest_id ; 

void xt_rateest_put(struct net *net, struct xt_rateest *est)
{
	struct xt_rateest_net *xn = net_generic(net, xt_rateest_id);

	mutex_lock(&xn->hash_lock);
	if (--est->refcnt == 0) {
		hlist_del(&est->list);
		gen_kill_estimator(&est->rate_est);
		/*
		 * gen_estimator est_timer() might access est->lock or bstats,
		 * wait a RCU grace period before freeing 'est'
		 */
		kfree_rcu(est, rcu);
	}
	mutex_unlock(&xn->hash_lock);
}