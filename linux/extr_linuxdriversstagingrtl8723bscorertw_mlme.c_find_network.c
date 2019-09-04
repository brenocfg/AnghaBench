#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {int fixed; TYPE_2__ network; } ;
struct mlme_priv {int /*<<< orphan*/  scanned_queue; struct wlan_network cur_network; } ;
struct TYPE_3__ {int asoc_sta_count; } ;
struct adapter {TYPE_1__ stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 struct wlan_network* rtw_find_network (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_network_nolock (struct adapter*,struct wlan_network*) ; 

__attribute__((used)) static void find_network(struct adapter *adapter)
{
	struct wlan_network *pwlan = NULL;
	struct	mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct wlan_network *tgt_network = &pmlmepriv->cur_network;

	pwlan = rtw_find_network(&pmlmepriv->scanned_queue, tgt_network->network.MacAddress);
	if (pwlan)
		pwlan->fixed = false;
	else
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("rtw_free_assoc_resources : pwlan == NULL\n\n"));


	if (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) &&
	    (adapter->stapriv.asoc_sta_count == 1))
		rtw_free_network_nolock(adapter, pwlan);
}