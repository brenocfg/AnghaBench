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
struct se_device {int /*<<< orphan*/  xcopy_lun; } ;
struct se_cmd {int /*<<< orphan*/  se_cmd_flags; struct se_device* se_dev; int /*<<< orphan*/ * se_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCF_SE_LUN_CMD ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_device*) ; 

__attribute__((used)) static void target_xcopy_init_pt_lun(struct se_device *se_dev,
		struct se_cmd *pt_cmd, bool remote_port)
{
	/*
	 * Don't allocate + init an pt_cmd->se_lun if honoring local port for
	 * reservations.  The pt_cmd->se_lun pointer will be setup from within
	 * target_xcopy_setup_pt_port()
	 */
	if (remote_port) {
		pr_debug("Setup emulated se_dev: %p from se_dev\n",
			pt_cmd->se_dev);
		pt_cmd->se_lun = &se_dev->xcopy_lun;
		pt_cmd->se_dev = se_dev;
	}

	pt_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
}