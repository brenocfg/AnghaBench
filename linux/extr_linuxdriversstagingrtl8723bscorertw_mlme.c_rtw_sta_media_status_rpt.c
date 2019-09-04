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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sta_info {int mac_id; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_H2C_MEDIA_STATUS_RPT ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtw_sta_media_status_rpt(struct adapter *adapter, struct sta_info *psta, u32 mstatus)
{
	u16 media_status_rpt;

	if (psta == NULL)
		return;

	media_status_rpt = (u16)((psta->mac_id<<8)|mstatus); /*   MACID|OPMODE:1 connect */
	rtw_hal_set_hwreg(adapter, HW_VAR_H2C_MEDIA_STATUS_RPT, (u8 *)&media_status_rpt);
}