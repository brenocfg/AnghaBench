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
struct tcf_mirred {int /*<<< orphan*/  tcfm_dev; int /*<<< orphan*/  tcfm_list; } ;
struct tc_action {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mirred_list_lock ; 
 struct net_device* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct tcf_mirred* to_mirred (struct tc_action*) ; 

__attribute__((used)) static void tcf_mirred_release(struct tc_action *a)
{
	struct tcf_mirred *m = to_mirred(a);
	struct net_device *dev;

	spin_lock(&mirred_list_lock);
	list_del(&m->tcfm_list);
	spin_unlock(&mirred_list_lock);

	/* last reference to action, no need to lock */
	dev = rcu_dereference_protected(m->tcfm_dev, 1);
	if (dev)
		dev_put(dev);
}