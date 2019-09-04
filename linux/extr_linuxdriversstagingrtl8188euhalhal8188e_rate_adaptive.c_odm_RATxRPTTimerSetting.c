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
typedef  scalar_t__ u16 ;
struct odm_dm_struct {scalar_t__ CurrminRptTime; int /*<<< orphan*/  Adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtw_rpt_timer_cfg_cmd (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
odm_RATxRPTTimerSetting(
		struct odm_dm_struct *dm_odm,
		u16 minRptTime
)
{
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE, (" =====>odm_RATxRPTTimerSetting()\n"));

	if (dm_odm->CurrminRptTime != minRptTime) {
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			     (" CurrminRptTime = 0x%04x minRptTime = 0x%04x\n", dm_odm->CurrminRptTime, minRptTime));
		rtw_rpt_timer_cfg_cmd(dm_odm->Adapter, minRptTime);
		dm_odm->CurrminRptTime = minRptTime;
	}
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE, (" <===== odm_RATxRPTTimerSetting()\n"));
}