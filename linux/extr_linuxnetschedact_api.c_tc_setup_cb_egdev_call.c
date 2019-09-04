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
struct tcf_action_egdev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int tcf_action_egdev_cb_call (struct tcf_action_egdev*,int,void*,int) ; 
 struct tcf_action_egdev* tcf_action_egdev_lookup (struct net_device const*) ; 

int tc_setup_cb_egdev_call(const struct net_device *dev,
			   enum tc_setup_type type, void *type_data,
			   bool err_stop)
{
	struct tcf_action_egdev *egdev = tcf_action_egdev_lookup(dev);

	if (!egdev)
		return 0;
	return tcf_action_egdev_cb_call(egdev, type, type_data, err_stop);
}