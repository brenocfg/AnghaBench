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
typedef  int u8 ;
struct TYPE_2__ {int bss_cnt; } ;
struct mlme_ext_priv {TYPE_1__ sitesurvey_res; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int GLBtcWiFiInScanState ; 

__attribute__((used)) static u8 halbtcoutsrc_GetWifiScanAPNum(struct adapter *padapter)
{
	struct mlme_ext_priv *pmlmeext;
	static u8 scan_AP_num;

	pmlmeext = &padapter->mlmeextpriv;

	if (GLBtcWiFiInScanState == false) {
		if (pmlmeext->sitesurvey_res.bss_cnt > 0xFF)
			scan_AP_num = 0xFF;
		else
			scan_AP_num = (u8)pmlmeext->sitesurvey_res.bss_cnt;
	}

	return scan_AP_num;
}