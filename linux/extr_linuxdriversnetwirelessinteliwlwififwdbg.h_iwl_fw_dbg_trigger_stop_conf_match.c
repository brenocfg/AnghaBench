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
struct TYPE_2__ {scalar_t__ conf; } ;
struct iwl_fw_runtime {TYPE_1__ dump; } ;
struct iwl_fw_dbg_trigger_tlv {int mode; int /*<<< orphan*/  stop_conf_ids; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 scalar_t__ FW_DBG_INVALID ; 
 int IWL_FW_DBG_TRIGGER_STOP ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
iwl_fw_dbg_trigger_stop_conf_match(struct iwl_fw_runtime *fwrt,
				   struct iwl_fw_dbg_trigger_tlv *trig)
{
	return ((trig->mode & IWL_FW_DBG_TRIGGER_STOP) &&
		(fwrt->dump.conf == FW_DBG_INVALID ||
		(BIT(fwrt->dump.conf) & le32_to_cpu(trig->stop_conf_ids))));
}