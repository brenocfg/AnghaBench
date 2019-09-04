#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; TYPE_2__* hw; } ;
struct TYPE_3__ {scalar_t__ num_qfull_cmds_dropped; scalar_t__ leak_exchg_thresh_hold; } ;
struct TYPE_4__ {int /*<<< orphan*/  cur_fw_xcb_count; TYPE_1__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_CTX_RESET_NEEDED ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 scalar_t__ IS_P3P_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlt_chk_exch_leak_thresh_hold(struct scsi_qla_host *vha)
{
	uint32_t total_leaked;

	total_leaked = vha->hw->tgt.num_qfull_cmds_dropped;

	if (vha->hw->tgt.leak_exchg_thresh_hold &&
	    (total_leaked > vha->hw->tgt.leak_exchg_thresh_hold)) {

		ql_dbg(ql_dbg_tgt, vha, 0xe079,
		    "Chip reset due to exchange starvation: %d/%d.\n",
		    total_leaked, vha->hw->cur_fw_xcb_count);

		if (IS_P3P_TYPE(vha->hw))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		else
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
	}

}