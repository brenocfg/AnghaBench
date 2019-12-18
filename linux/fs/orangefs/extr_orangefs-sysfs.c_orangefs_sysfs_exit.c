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
 int /*<<< orphan*/  GOSSIP_SYSFS_DEBUG ; 
 int /*<<< orphan*/  acache_orangefs_obj ; 
 int /*<<< orphan*/  capcache_orangefs_obj ; 
 int /*<<< orphan*/  ccache_orangefs_obj ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncache_orangefs_obj ; 
 int /*<<< orphan*/  orangefs_obj ; 
 int /*<<< orphan*/  pc_orangefs_obj ; 
 int /*<<< orphan*/  stats_orangefs_obj ; 

void orangefs_sysfs_exit(void)
{
	gossip_debug(GOSSIP_SYSFS_DEBUG, "orangefs_sysfs_exit: start\n");
	kobject_put(acache_orangefs_obj);
	kobject_put(capcache_orangefs_obj);
	kobject_put(ccache_orangefs_obj);
	kobject_put(ncache_orangefs_obj);
	kobject_put(pc_orangefs_obj);
	kobject_put(stats_orangefs_obj);
	kobject_put(orangefs_obj);
}