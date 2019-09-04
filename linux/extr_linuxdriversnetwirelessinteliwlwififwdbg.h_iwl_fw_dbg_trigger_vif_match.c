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
typedef  scalar_t__ u32 ;
struct wireless_dev {scalar_t__ iftype; } ;
struct iwl_fw_dbg_trigger_tlv {int /*<<< orphan*/  vif_type; } ;

/* Variables and functions */
 scalar_t__ IWL_FW_DBG_CONF_VIF_ANY ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
iwl_fw_dbg_trigger_vif_match(struct iwl_fw_dbg_trigger_tlv *trig,
			     struct wireless_dev *wdev)
{
	u32 trig_vif = le32_to_cpu(trig->vif_type);

	return trig_vif == IWL_FW_DBG_CONF_VIF_ANY ||
	       wdev->iftype == trig_vif;
}