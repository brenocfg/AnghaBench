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
typedef  scalar_t__ u8 ;
struct adapter {int /*<<< orphan*/  mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_DL_RSVD_PAGE ; 
 scalar_t__ RT_MEDIA_CONNECT ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal_btcoex_MediaStatusNotify (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtw_btcoex_MediaStatusNotify(struct adapter *padapter, u8 mediaStatus)
{
	if ((mediaStatus == RT_MEDIA_CONNECT)
		&& (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true)) {
		rtw_hal_set_hwreg(padapter, HW_VAR_DL_RSVD_PAGE, NULL);
	}

	hal_btcoex_MediaStatusNotify(padapter, mediaStatus);
}