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
typedef  int /*<<< orphan*/  tc_setup_cb_t ;
struct tcf_action_egdev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  tcf_action_egdev_cb_del (struct tcf_action_egdev*,int /*<<< orphan*/ *,void*) ; 
 struct tcf_action_egdev* tcf_action_egdev_lookup (struct net_device const*) ; 
 int /*<<< orphan*/  tcf_action_egdev_put (struct tcf_action_egdev*) ; 

__attribute__((used)) static void __tc_setup_cb_egdev_unregister(const struct net_device *dev,
					   tc_setup_cb_t *cb, void *cb_priv)
{
	struct tcf_action_egdev *egdev = tcf_action_egdev_lookup(dev);

	if (WARN_ON(!egdev))
		return;
	tcf_action_egdev_cb_del(egdev, cb, cb_priv);
	tcf_action_egdev_put(egdev);
}