#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  IELength; scalar_t__ IEs; } ;
struct TYPE_8__ {TYPE_3__ network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct TYPE_9__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  WLAN_BSSID_EX ;
typedef  int /*<<< orphan*/  NDIS_802_11_FIXED_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_same_network (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_update_protection (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_network (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void update_current_network(_adapter *adapter, WLAN_BSSID_EX *pnetwork)
{
	struct	mlme_priv	*pmlmepriv = &(adapter->mlmepriv);
	
_func_enter_;		

#ifdef PLATFORM_OS_XP
	if ((unsigned long)(&(pmlmepriv->cur_network.network)) < 0x7ffffff)
	{		
		KeBugCheckEx(0x87111c1c, (ULONG_PTR)(&(pmlmepriv->cur_network.network)), 0, 0,0);
	}
#endif

	if ( (check_fwstate(pmlmepriv, _FW_LINKED)== _TRUE) && (is_same_network(&(pmlmepriv->cur_network.network), pnetwork)))
	{
		//RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,"Same Network\n");

		//if(pmlmepriv->cur_network.network.IELength<= pnetwork->IELength)
		{
			update_network(&(pmlmepriv->cur_network.network), pnetwork,adapter, _TRUE);
			rtw_update_protection(adapter, (pmlmepriv->cur_network.network.IEs) + sizeof (NDIS_802_11_FIXED_IEs), 
									pmlmepriv->cur_network.network.IELength);
		}
	}

_func_exit_;			

}