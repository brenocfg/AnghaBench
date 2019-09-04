#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_3__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */

void rtw_joinbss_reset(_adapter *padapter)
{
	u8	threshold;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;

#ifdef CONFIG_80211N_HT	
	struct ht_priv		*phtpriv = &pmlmepriv->htpriv;
#endif

	//todo: if you want to do something io/reg/hw setting before join_bss, please add code here
	



#ifdef CONFIG_80211N_HT

	pmlmepriv->num_FortyMHzIntolerant = 0;

	pmlmepriv->num_sta_no_ht = 0;

	phtpriv->ampdu_enable = _FALSE;//reset to disabled

#ifdef CONFIG_USB_HCI
	// TH=1 => means that invalidate usb rx aggregation
	// TH=0 => means that validate usb rx aggregation, use init value.
	if(phtpriv->ht_option)
	{
		if(padapter->registrypriv.wifi_spec==1)		
			threshold = 1;
		else
			threshold = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
	}
	else
	{
		threshold = 1;
		rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
	}
#endif

#endif	

}