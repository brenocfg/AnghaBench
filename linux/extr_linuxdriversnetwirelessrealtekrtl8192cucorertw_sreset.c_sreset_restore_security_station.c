#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct security_priv {scalar_t__ dot11PrivacyAlgrthm; int /*<<< orphan*/  dot118021XGrpKeyid; } ;
struct mlme_priv {int dummy; } ;
struct mlme_ext_info {scalar_t__ auth_algo; } ;
struct TYPE_7__ {struct mlme_ext_info mlmext_info; } ;
struct TYPE_8__ {struct security_priv securitypriv; TYPE_1__ mlmeextpriv; struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_SEC_CFG ; 
 scalar_t__ _AES_ ; 
 scalar_t__ _TKIP_ ; 
 int /*<<< orphan*/  _TRUE ; 
 scalar_t__ dot11AuthAlgrthm_8021X ; 
 int /*<<< orphan*/  get_bssid (struct mlme_priv*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_set_key (TYPE_2__*,struct security_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_setstakey_cmd (TYPE_2__*,unsigned char*,int /*<<< orphan*/ ) ; 

void sreset_restore_security_station(_adapter *padapter)
{
	u8 EntryId = 0;
	struct mlme_priv *mlmepriv = &padapter->mlmepriv;
	struct sta_priv * pstapriv = &padapter->stapriv;
	struct sta_info *psta;
	struct security_priv* psecuritypriv=&(padapter->securitypriv);
	struct mlme_ext_info	*pmlmeinfo = &padapter->mlmeextpriv.mlmext_info;

	{
		u8 val8;

		if (pmlmeinfo->auth_algo == dot11AuthAlgrthm_8021X) {
			val8 = 0xcc;
		#ifdef CONFIG_WAPI_SUPPORT
		} else if (padapter->wapiInfo.bWapiEnable && pmlmeinfo->auth_algo == dot11AuthAlgrthm_WAPI) {
			//Disable TxUseDefaultKey, RxUseDefaultKey, RxBroadcastUseDefaultKey.
			val8 = 0x4c;
		#endif
		} else {
			val8 = 0xcf;
		}
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));
	}

	#if 0
	if (	( padapter->securitypriv.dot11PrivacyAlgrthm == _WEP40_ ) ||
		( padapter->securitypriv.dot11PrivacyAlgrthm == _WEP104_ ))
	{

		for(EntryId=0; EntryId<4; EntryId++)
		{
			if(EntryId == psecuritypriv->dot11PrivacyKeyIndex)
				rtw_set_key(padapter,&padapter->securitypriv, EntryId, 1);
			else
				rtw_set_key(padapter,&padapter->securitypriv, EntryId, 0);
		}

	}
	else
	#endif
	if((padapter->securitypriv.dot11PrivacyAlgrthm == _TKIP_) ||
		(padapter->securitypriv.dot11PrivacyAlgrthm == _AES_))
	{
		psta = rtw_get_stainfo(pstapriv, get_bssid(mlmepriv));
		if (psta == NULL) {
			//DEBUG_ERR( ("Set wpa_set_encryption: Obtain Sta_info fail \n"));
		}
		else
		{
			//pairwise key
			rtw_setstakey_cmd(padapter, (unsigned char *)psta, _TRUE);
			//group key
			rtw_set_key(padapter,&padapter->securitypriv,padapter->securitypriv.dot118021XGrpKeyid, 0);
		}
	}
}