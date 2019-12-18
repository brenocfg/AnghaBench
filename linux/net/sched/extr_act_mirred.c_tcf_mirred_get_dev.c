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
typedef  int /*<<< orphan*/  tc_action_priv_destructor ;
struct tcf_mirred {int /*<<< orphan*/  tcfm_dev; } ;
struct tc_action {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tcf_mirred_dev_put ; 
 struct tcf_mirred* to_mirred (struct tc_action const*) ; 

__attribute__((used)) static struct net_device *
tcf_mirred_get_dev(const struct tc_action *a,
		   tc_action_priv_destructor *destructor)
{
	struct tcf_mirred *m = to_mirred(a);
	struct net_device *dev;

	rcu_read_lock();
	dev = rcu_dereference(m->tcfm_dev);
	if (dev) {
		dev_hold(dev);
		*destructor = tcf_mirred_dev_put;
	}
	rcu_read_unlock();

	return dev;
}