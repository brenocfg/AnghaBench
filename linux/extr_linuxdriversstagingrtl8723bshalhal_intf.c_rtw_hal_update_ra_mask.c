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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int /*<<< orphan*/  mac_id; struct adapter* padapter; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* UpdateRAMaskHandler ) (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct adapter {TYPE_1__ HalFunc; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  add_RATid (struct adapter*,struct sta_info*,int /*<<< orphan*/ ) ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_hal_update_ra_mask(struct sta_info *psta, u8 rssi_level)
{
	struct adapter *padapter;
	struct mlme_priv *pmlmepriv;

	if (!psta)
		return;

	padapter = psta->padapter;

	pmlmepriv = &(padapter->mlmepriv);

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
		add_RATid(padapter, psta, rssi_level);
	else {
		if (padapter->HalFunc.UpdateRAMaskHandler)
			padapter->HalFunc.UpdateRAMaskHandler(padapter, psta->mac_id, rssi_level);
	}
}