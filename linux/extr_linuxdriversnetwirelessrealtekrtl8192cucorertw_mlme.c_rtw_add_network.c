#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlme_priv {int dummy; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_5__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_update_scanned_network (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_current_network (TYPE_1__*,int /*<<< orphan*/ *) ; 

void rtw_add_network(_adapter *adapter, WLAN_BSSID_EX *pnetwork)
{
	_irqL irqL;
	struct	mlme_priv	*pmlmepriv = &(((_adapter *)adapter)->mlmepriv);
	//_queue	*queue	= &(pmlmepriv->scanned_queue);

_func_enter_;		

	//_enter_critical_bh(&queue->lock, &irqL);

	#if defined(CONFIG_P2P) && defined(CONFIG_P2P_REMOVE_GROUP_INFO)
	rtw_WLAN_BSSID_EX_remove_p2p_attr(pnetwork, P2P_ATTR_GROUP_INFO);
	#endif
	
	update_current_network(adapter, pnetwork);
	
	rtw_update_scanned_network(adapter, pnetwork);

	//_exit_critical_bh(&queue->lock, &irqL);
	
_func_exit_;		
}