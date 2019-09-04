#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {int fw_dumped; int /*<<< orphan*/  fw_dump_cap_flags; int /*<<< orphan*/  fw_dump; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_no; struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  QLA_UEVENT_CODE_FW_DUMP ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_post_uevent_work (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
qla2xxx_dump_post_process(scsi_qla_host_t *vha, int rval)
{
	struct qla_hw_data *ha = vha->hw;

	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0xd000,
		    "Failed to dump firmware (%x), dump status flags (0x%lx).\n",
		    rval, ha->fw_dump_cap_flags);
		ha->fw_dumped = 0;
	} else {
		ql_log(ql_log_info, vha, 0xd001,
		    "Firmware dump saved to temp buffer (%ld/%p), dump status flags (0x%lx).\n",
		    vha->host_no, ha->fw_dump, ha->fw_dump_cap_flags);
		ha->fw_dumped = 1;
		qla2x00_post_uevent_work(vha, QLA_UEVENT_CODE_FW_DUMP);
	}
}