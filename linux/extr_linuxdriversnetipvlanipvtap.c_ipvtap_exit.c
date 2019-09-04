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

/* Variables and functions */
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipvtap_cdev ; 
 int /*<<< orphan*/  ipvtap_class ; 
 int /*<<< orphan*/  ipvtap_link_ops ; 
 int /*<<< orphan*/  ipvtap_major ; 
 int /*<<< orphan*/  ipvtap_notifier_block ; 
 int /*<<< orphan*/  rtnl_link_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tap_destroy_cdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipvtap_exit(void)
{
	rtnl_link_unregister(&ipvtap_link_ops);
	unregister_netdevice_notifier(&ipvtap_notifier_block);
	class_unregister(&ipvtap_class);
	tap_destroy_cdev(ipvtap_major, &ipvtap_cdev);
}