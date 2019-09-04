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
 int ENOMEM ; 
 int tcf_action_egdev_cb_add (struct tcf_action_egdev*,int /*<<< orphan*/ *,void*) ; 
 struct tcf_action_egdev* tcf_action_egdev_get (struct net_device const*) ; 
 int /*<<< orphan*/  tcf_action_egdev_put (struct tcf_action_egdev*) ; 

__attribute__((used)) static int __tc_setup_cb_egdev_register(const struct net_device *dev,
					tc_setup_cb_t *cb, void *cb_priv)
{
	struct tcf_action_egdev *egdev = tcf_action_egdev_get(dev);
	int err;

	if (!egdev)
		return -ENOMEM;
	err = tcf_action_egdev_cb_add(egdev, cb, cb_priv);
	if (err)
		goto err_cb_add;
	return 0;

err_cb_add:
	tcf_action_egdev_put(egdev);
	return err;
}