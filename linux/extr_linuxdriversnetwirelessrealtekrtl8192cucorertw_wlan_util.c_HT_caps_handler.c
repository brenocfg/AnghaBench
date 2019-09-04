#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct registry_priv {scalar_t__ special_rf_path; } ;
struct ht_priv {scalar_t__ ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct TYPE_9__ {int AMPDU_para; int /*<<< orphan*/ * MCS_rate; void* HT_ext_caps; void* HT_caps_info; } ;
struct TYPE_10__ {int* HT_cap; TYPE_1__ HT_cap_element; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
struct mlme_ext_info {int HT_caps_enable; TYPE_3__ HT_caps; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_12__ {struct registry_priv registrypriv; struct mlme_priv mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_4__ _adapter ;
struct TYPE_13__ {unsigned int Length; int* data; } ;
typedef  TYPE_5__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_RF_TYPE ; 
 int /*<<< orphan*/ * MCS_rate_1R ; 
 int /*<<< orphan*/ * MCS_rate_2R ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ _FALSE ; 
 void* le16_to_cpu (void*) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__*) ; 

void HT_caps_handler(_adapter *padapter, PNDIS_802_11_VARIABLE_IEs pIE)
{
	unsigned int	i;
	u8	rf_type;
	u8	max_AMPDU_len, min_MPDU_spacing;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct mlme_priv 		*pmlmepriv = &padapter->mlmepriv;	
	struct ht_priv			*phtpriv = &pmlmepriv->htpriv;
	struct registry_priv 	*pregistrypriv = &padapter->registrypriv;
	
	if(pIE==NULL) return;
	
	if(phtpriv->ht_option == _FALSE)	return;

	pmlmeinfo->HT_caps_enable = 1;
	
	for (i = 0; i < (pIE->Length); i++)
	{
		if (i != 2)
		{
			//	Commented by Albert 2010/07/12
			//	Got the endian issue here.
			pmlmeinfo->HT_caps.u.HT_cap[i] &= (pIE->data[i]);
		}
		else
		{
			//modify from  fw by Thomas 2010/11/17
			if ((pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x3) > (pIE->data[i] & 0x3))
			{
				max_AMPDU_len = (pIE->data[i] & 0x3);
			}
			else
			{
				max_AMPDU_len = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x3);
			}
			
			if ((pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x1c) > (pIE->data[i] & 0x1c))
			{
				min_MPDU_spacing = (pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para & 0x1c);
			}
			else
			{
				min_MPDU_spacing = (pIE->data[i] & 0x1c);
			}

			pmlmeinfo->HT_caps.u.HT_cap_element.AMPDU_para = max_AMPDU_len | min_MPDU_spacing;
		}
	}

	//	Commented by Albert 2010/07/12
	//	Have to handle the endian issue after copying.
	//	HT_ext_caps didn't be used yet.	
	pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info = le16_to_cpu( pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info );
	pmlmeinfo->HT_caps.u.HT_cap_element.HT_ext_caps = le16_to_cpu( pmlmeinfo->HT_caps.u.HT_cap_element.HT_ext_caps );

	rtw_hal_get_hwreg(padapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

	//update the MCS rates
	for (i = 0; i < 16; i++)
	{
		if((rf_type == RF_1T1R) || (rf_type == RF_1T2R))
		{
			pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= MCS_rate_1R[i];
		}
		else
		{
			#ifdef CONFIG_DISABLE_MCS13TO15
			if(pmlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40 && (pregistrypriv->wifi_spec!=1))
				pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= MCS_rate_2R_MCS13TO15_OFF[i];
			else
			pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= MCS_rate_2R[i];
			#else
			pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= MCS_rate_2R[i];
			#endif //CONFIG_DISABLE_MCS13TO15
		}
	        #ifdef RTL8192C_RECONFIG_TO_1T1R
		{
			pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= MCS_rate_1R[i];
		}
		#endif

		if(pregistrypriv->special_rf_path)
			pmlmeinfo->HT_caps.u.HT_cap_element.MCS_rate[i] &= MCS_rate_1R[i];

	}
	
	return;
}