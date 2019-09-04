#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ qos_option; } ;
struct mlme_priv {TYPE_1__ qospriv; } ;
struct mlme_ext_info {int WMM_enable; int /*<<< orphan*/  WMM_param; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct WMM_para_element {int dummy; } ;
struct TYPE_7__ {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_3__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 int _FAIL ; 
 int _TRUE ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

int WMM_param_handler(_adapter *padapter, PNDIS_802_11_VARIABLE_IEs	pIE)
{
	//struct registry_priv	*pregpriv = &padapter->registrypriv;
	struct mlme_priv	*pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);	
	
	if(pmlmepriv->qospriv.qos_option==0)
	{
		pmlmeinfo->WMM_enable = 0;
		return _FAIL;
	}	

	pmlmeinfo->WMM_enable = 1;
	_rtw_memcpy(&(pmlmeinfo->WMM_param), (pIE->data + 6), sizeof(struct WMM_para_element));
	return _TRUE;

	/*if (pregpriv->wifi_spec == 1)
	{
		if (pmlmeinfo->WMM_enable == 1)
		{
			//todo: compare the parameter set count & decide wheher to update or not
			return _FAIL;
		}
		else
		{
			pmlmeinfo->WMM_enable = 1;
			_rtw_rtw_memcpy(&(pmlmeinfo->WMM_param), (pIE->data + 6), sizeof(struct WMM_para_element));
			return _TRUE;
		}
	}
	else
	{
		pmlmeinfo->WMM_enable = 0;
		return _FAIL;
	}*/
	
}