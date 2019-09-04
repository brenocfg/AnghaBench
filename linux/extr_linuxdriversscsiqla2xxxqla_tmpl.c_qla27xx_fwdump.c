#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_6__ {TYPE_5__* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  hardware_lock; int /*<<< orphan*/  fw_dump; scalar_t__ fw_dumped; int /*<<< orphan*/  fw_dump_template; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_FW_STOPPED (TYPE_5__*) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla27xx_execute_fwdt_template (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
qla27xx_fwdump(scsi_qla_host_t *vha, int hardware_locked)
{
	ulong flags = 0;

#ifndef __CHECKER__
	if (!hardware_locked)
		spin_lock_irqsave(&vha->hw->hardware_lock, flags);
#endif

	if (!vha->hw->fw_dump)
		ql_log(ql_log_warn, vha, 0xd01e, "fwdump buffer missing.\n");
	else if (!vha->hw->fw_dump_template)
		ql_log(ql_log_warn, vha, 0xd01f, "fwdump template missing.\n");
	else if (vha->hw->fw_dumped)
		ql_log(ql_log_warn, vha, 0xd300,
		    "Firmware has been previously dumped (%p),"
		    " -- ignoring request\n", vha->hw->fw_dump);
	else {
		QLA_FW_STOPPED(vha->hw);
		qla27xx_execute_fwdt_template(vha);
	}

#ifndef __CHECKER__
	if (!hardware_locked)
		spin_unlock_irqrestore(&vha->hw->hardware_lock, flags);
#endif
}