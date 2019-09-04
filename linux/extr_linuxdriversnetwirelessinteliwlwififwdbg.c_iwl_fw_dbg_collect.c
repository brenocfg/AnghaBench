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
struct iwl_fw_runtime {int /*<<< orphan*/  trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
struct iwl_fw_dump_desc {size_t len; TYPE_1__ trig_desc; } ;
struct iwl_fw_dbg_trigger_tlv {int flags; } ;
typedef  enum iwl_fw_dbg_trigger { ____Placeholder_iwl_fw_dbg_trigger } iwl_fw_dbg_trigger ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IWL_FW_DBG_FORCE_RESTART ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_fw_runtime*,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_force_nmi (int /*<<< orphan*/ ) ; 
 int iwl_fw_dbg_collect_desc (struct iwl_fw_runtime*,struct iwl_fw_dump_desc*,struct iwl_fw_dbg_trigger_tlv const*) ; 
 struct iwl_fw_dump_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 

int iwl_fw_dbg_collect(struct iwl_fw_runtime *fwrt,
		       enum iwl_fw_dbg_trigger trig,
		       const char *str, size_t len,
		       const struct iwl_fw_dbg_trigger_tlv *trigger)
{
	struct iwl_fw_dump_desc *desc;

	if (trigger && trigger->flags & IWL_FW_DBG_FORCE_RESTART) {
		IWL_WARN(fwrt, "Force restart: trigger %d fired.\n", trig);
		iwl_force_nmi(fwrt->trans);
		return 0;
	}

	desc = kzalloc(sizeof(*desc) + len, GFP_ATOMIC);
	if (!desc)
		return -ENOMEM;

	desc->len = len;
	desc->trig_desc.type = cpu_to_le32(trig);
	memcpy(desc->trig_desc.data, str, len);

	return iwl_fw_dbg_collect_desc(fwrt, desc, trigger);
}