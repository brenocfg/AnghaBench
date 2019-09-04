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
typedef  scalar_t__ u8 ;
struct sta_info {int /*<<< orphan*/  hwaddr; } ;
struct mlme_ext_info {int accept_addba_req; } ;
struct TYPE_2__ {struct mlme_ext_info mlmext_info; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; int /*<<< orphan*/  stapriv; TYPE_1__ mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_bssid (int /*<<< orphan*/ *) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_delba (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_btcoex_RejectApAggregatedPacket(struct adapter *padapter, u8 enable)
{
	struct mlme_ext_info *pmlmeinfo;
	struct sta_info *psta;

	pmlmeinfo = &padapter->mlmeextpriv.mlmext_info;
	psta = rtw_get_stainfo(&padapter->stapriv, get_bssid(&padapter->mlmepriv));

	if (enable) {
		pmlmeinfo->accept_addba_req = false;
		if (psta)
			send_delba(padapter, 0, psta->hwaddr);
	} else {
		pmlmeinfo->accept_addba_req = true;
	}
}