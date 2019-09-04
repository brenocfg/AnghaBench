#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct mlme_ext_info {TYPE_1__* FW_sta_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ SupportedRates; } ;
typedef  TYPE_3__* PNDIS_802_11_VARIABLE_IEs ;

/* Variables and functions */
 int /*<<< orphan*/  _EXT_SUPPORTEDRATES_IE_ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _SUPPORTEDRATES_IE_ ; 
 int /*<<< orphan*/  _rtw_memcpy (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ rtw_get_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 

int update_sta_support_rate(_adapter *padapter, u8* pvar_ie, uint var_ie_len, int cam_idx)
{
	unsigned int	ie_len;
	PNDIS_802_11_VARIABLE_IEs	pIE;
	int	supportRateNum = 0;
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	
	pIE = (PNDIS_802_11_VARIABLE_IEs)rtw_get_ie(pvar_ie, _SUPPORTEDRATES_IE_, &ie_len, var_ie_len);
	if (pIE == NULL)
	{
		return _FAIL;
	}
	
	_rtw_memcpy(pmlmeinfo->FW_sta_info[cam_idx].SupportedRates, pIE->data, ie_len);
	supportRateNum = ie_len;
				
	pIE = (PNDIS_802_11_VARIABLE_IEs)rtw_get_ie(pvar_ie, _EXT_SUPPORTEDRATES_IE_, &ie_len, var_ie_len);
	if (pIE)
	{
		_rtw_memcpy((pmlmeinfo->FW_sta_info[cam_idx].SupportedRates + supportRateNum), pIE->data, ie_len);
	}

	return _SUCCESS;
	
}