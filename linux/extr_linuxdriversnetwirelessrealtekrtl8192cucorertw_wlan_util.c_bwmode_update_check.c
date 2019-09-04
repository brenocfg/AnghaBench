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
typedef  int u8 ;
struct sta_priv {int dummy; } ;
struct ht_priv {scalar_t__ ht_option; unsigned char bwmode; unsigned char ch_offset; } ;
struct sta_info {struct ht_priv htpriv; } ;
struct registry_priv {int cbw40_enable; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct TYPE_9__ {int /*<<< orphan*/  MacAddress; } ;
struct mlme_ext_info {scalar_t__ bwmode_updated; TYPE_2__ network; } ;
struct mlme_ext_priv {int cur_channel; unsigned char cur_bwmode; unsigned char cur_ch_offset; struct mlme_ext_info mlmext_info; } ;
struct HT_info_element {int* infos; } ;
struct TYPE_8__ {struct sta_priv stapriv; struct registry_priv registrypriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  TYPE_2__ WLAN_BSSID_EX ;
struct TYPE_10__ {int Length; scalar_t__ data; } ;
typedef  TYPE_3__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 int BIT (int) ; 
 void* HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 unsigned char HAL_PRIME_CHNL_OFFSET_LOWER ; 
 unsigned char HAL_PRIME_CHNL_OFFSET_UPPER ; 
 void* HT_CHANNEL_WIDTH_20 ; 
 unsigned char HT_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  HT_info_handler (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _TRUE ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwmode_update_check(_adapter *padapter, PNDIS_802_11_VARIABLE_IEs pIE)
{
	unsigned char	 new_bwmode;
	unsigned char  new_ch_offset;
	struct HT_info_element	 *pHT_info;
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct registry_priv *pregistrypriv = &padapter->registrypriv;
	struct ht_priv			*phtpriv = &pmlmepriv->htpriv;
	u8 cbw40_enable=0;

	if(!pIE)
		return;

	if(phtpriv->ht_option == _FALSE)	return;

	if(pIE->Length > sizeof(struct HT_info_element))
		return;
	
	pHT_info = (struct HT_info_element *)pIE->data;

	if (pmlmeext->cur_channel > 14) {
		if (pregistrypriv->cbw40_enable & BIT(1))
			cbw40_enable = 1;
	} else {
		if (pregistrypriv->cbw40_enable & BIT(0))
			cbw40_enable = 1;
	}
	
	if((pHT_info->infos[0] & BIT(2)) && cbw40_enable )
	{
		new_bwmode = HT_CHANNEL_WIDTH_40;

		switch (pHT_info->infos[0] & 0x3)
		{
			case 1:
				new_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
				break;
			
			case 3:
				new_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
				break;
				
			default:
				new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
				break;
		}
	}
	else
	{
		new_bwmode = HT_CHANNEL_WIDTH_20;
		new_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	}	

	
	if((new_bwmode!= pmlmeext->cur_bwmode) || (new_ch_offset!=pmlmeext->cur_ch_offset))
	{
		pmlmeinfo->bwmode_updated = _TRUE;
		
		pmlmeext->cur_bwmode = new_bwmode;
		pmlmeext->cur_ch_offset = new_ch_offset;

		//update HT info also
		HT_info_handler(padapter, pIE);
	}
	else
	{
		pmlmeinfo->bwmode_updated = _FALSE;
	}
		

	if(_TRUE == pmlmeinfo->bwmode_updated)
	{
		struct sta_info *psta;
		WLAN_BSSID_EX 	*cur_network = &(pmlmeinfo->network);
		struct sta_priv	*pstapriv = &padapter->stapriv;
	
		//set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		
		//update ap's stainfo
		psta = rtw_get_stainfo(pstapriv, cur_network->MacAddress);
		if(psta)
		{
			struct ht_priv	*phtpriv_sta = &psta->htpriv;
			
			if(phtpriv_sta->ht_option)
			{				
				// bwmode				
				phtpriv_sta->bwmode = pmlmeext->cur_bwmode;
				phtpriv_sta->ch_offset = pmlmeext->cur_ch_offset;		
			}
			else
			{
				phtpriv_sta->bwmode = HT_CHANNEL_WIDTH_20;
				phtpriv_sta->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
			}
			
		}

		//pmlmeinfo->bwmode_updated = _FALSE;//bwmode_updated done, reset it!
		
	}	

}