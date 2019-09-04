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
struct wlan_network {int dummy; } ;
struct mlme_priv {scalar_t__ free_bss_buf; } ;

/* Variables and functions */
 int MAX_BSS_CNT ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_free_mlme_priv_ie_data (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_mfree_mlme_priv_lock (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_vmfree (scalar_t__,int) ; 

void _rtw_free_mlme_priv (struct mlme_priv *pmlmepriv)
{
_func_enter_;

	rtw_free_mlme_priv_ie_data(pmlmepriv);

	if(pmlmepriv){
		rtw_mfree_mlme_priv_lock (pmlmepriv);

		if (pmlmepriv->free_bss_buf) {
			rtw_vmfree(pmlmepriv->free_bss_buf, MAX_BSS_CNT * sizeof(struct wlan_network));
		}
	}
_func_exit_;	
}