#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  wk; struct iwl_fw_dbg_trigger_tlv const* trig; struct iwl_fw_dump_desc const* desc; } ;
struct TYPE_6__ {scalar_t__ num_lmacs; } ;
struct iwl_fw_runtime {TYPE_4__ dump; int /*<<< orphan*/  status; TYPE_2__ smem_cfg; TYPE_1__* trans; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct iwl_fw_dump_desc {TYPE_3__ trig_desc; } ;
struct iwl_fw_dbg_trigger_tlv {int /*<<< orphan*/  stop_delay; } ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_FWRT_STATUS_DUMPING ; 
 scalar_t__ IWL_TRANS_NO_FW ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_fw_runtime*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN (int,char*) ; 
 scalar_t__ WARN_ON (struct iwl_fw_dump_desc const*) ; 
 int /*<<< orphan*/  iwl_fw_free_dump_desc (struct iwl_fw_runtime*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_fw_dbg_collect_desc(struct iwl_fw_runtime *fwrt,
			    const struct iwl_fw_dump_desc *desc,
			    const struct iwl_fw_dbg_trigger_tlv *trigger)
{
	unsigned int delay = 0;

	if (trigger)
		delay = msecs_to_jiffies(le32_to_cpu(trigger->stop_delay));

	/*
	 * If the loading of the FW completed successfully, the next step is to
	 * get the SMEM config data. Thus, if fwrt->smem_cfg.num_lmacs is non
	 * zero, the FW was already loaded successully. If the state is "NO_FW"
	 * in such a case - WARN and exit, since FW may be dead. Otherwise, we
	 * can try to collect the data, since FW might just not be fully
	 * loaded (no "ALIVE" yet), and the debug data is accessible.
	 *
	 * Corner case: got the FW alive but crashed before getting the SMEM
	 *	config. In such a case, due to HW access problems, we might
	 *	collect garbage.
	 */
	if (WARN((fwrt->trans->state == IWL_TRANS_NO_FW) &&
		 fwrt->smem_cfg.num_lmacs,
		 "Can't collect dbg data when FW isn't alive\n"))
		return -EIO;

	if (test_and_set_bit(IWL_FWRT_STATUS_DUMPING, &fwrt->status))
		return -EBUSY;

	if (WARN_ON(fwrt->dump.desc))
		iwl_fw_free_dump_desc(fwrt);

	IWL_WARN(fwrt, "Collecting data: trigger %d fired.\n",
		 le32_to_cpu(desc->trig_desc.type));

	fwrt->dump.desc = desc;
	fwrt->dump.trig = trigger;

	schedule_delayed_work(&fwrt->dump.wk, delay);

	return 0;
}