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
typedef  int u32 ;
struct iscsi_tpg_attrib {int demo_mode_write_protect; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; struct iscsi_tpg_attrib tpg_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int iscsit_ta_demo_mode_write_protect(
	struct iscsi_portal_group *tpg,
	u32 flag)
{
	struct iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	if ((flag != 0) && (flag != 1)) {
		pr_err("Illegal value %d\n", flag);
		return -EINVAL;
	}

	a->demo_mode_write_protect = flag;
	pr_debug("iSCSI_TPG[%hu] - Demo Mode Write Protect bit: %s\n",
		tpg->tpgt, (a->demo_mode_write_protect) ? "ON" : "OFF");

	return 0;
}