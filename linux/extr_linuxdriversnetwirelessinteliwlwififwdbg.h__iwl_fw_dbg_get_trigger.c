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
struct iwl_fw_dbg_trigger_tlv {int dummy; } ;
struct iwl_fw {struct iwl_fw_dbg_trigger_tlv** dbg_trigger_tlv; } ;
typedef  enum iwl_fw_dbg_trigger { ____Placeholder_iwl_fw_dbg_trigger } iwl_fw_dbg_trigger ;

/* Variables and functions */

__attribute__((used)) static inline struct iwl_fw_dbg_trigger_tlv*
_iwl_fw_dbg_get_trigger(const struct iwl_fw *fw, enum iwl_fw_dbg_trigger id)
{
	return fw->dbg_trigger_tlv[id];
}