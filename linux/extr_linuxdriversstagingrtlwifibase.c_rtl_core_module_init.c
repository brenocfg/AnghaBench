#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  glb_list_lock; int /*<<< orphan*/  glb_priv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl_debugfs_add_topdir () ; 
 TYPE_1__ rtl_global_var ; 
 scalar_t__ rtl_rate_control_register () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int rtl_core_module_init(void)
{
	if (rtl_rate_control_register())
		pr_err("rtl: Unable to register rtl_rc, use default RC !!\n");

	/* add debugfs */
	rtl_debugfs_add_topdir();

	/* init some global vars */
	INIT_LIST_HEAD(&rtl_global_var.glb_priv_list);
	spin_lock_init(&rtl_global_var.glb_list_lock);

	return 0;
}