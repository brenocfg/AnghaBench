#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int u8 ;
struct security_priv {scalar_t__ ndisauthtype; scalar_t__ ndisencryptstatus; int* wps_ie; int wps_ie_len; int* supplicant_ie; } ;
struct mlme_priv {int /*<<< orphan*/  assoc_bssid; } ;
typedef  scalar_t__ sint ;
struct TYPE_6__ {struct security_priv securitypriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ Ndis802_11AuthModeWPA ; 
 scalar_t__ Ndis802_11AuthModeWPA2 ; 
 scalar_t__ Ndis802_11AuthModeWPA2PSK ; 
 scalar_t__ Ndis802_11AuthModeWPAPSK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int SecIsInPMKIDList (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_UNDER_WPS ; 
 int _WPA2_IE_ID_ ; 
 int _WPA_IE_ID_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int*,int*,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_append_pmkid (TYPE_1__*,int,int*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_report_sec_ie (TYPE_1__*,int,int*) ; 

sint rtw_restruct_sec_ie(_adapter *adapter,u8 *in_ie, u8 *out_ie, uint in_len)
{
	u8 authmode, securitytype, match;
	u8 sec_ie[255], uncst_oui[4], bkup_ie[255];
	u8 wpa_oui[4]={0x0, 0x50, 0xf2, 0x01};
	uint 	ielength, cnt, remove_cnt;
	int iEntry;

	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct security_priv *psecuritypriv=&adapter->securitypriv;
	uint 	ndisauthmode=psecuritypriv->ndisauthtype;
	uint ndissecuritytype = psecuritypriv->ndisencryptstatus;
	
_func_enter_;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_,
		 ("+rtw_restruct_sec_ie: ndisauthmode=%d ndissecuritytype=%d\n",
		  ndisauthmode, ndissecuritytype));
	
	//copy fixed ie only
	_rtw_memcpy(out_ie, in_ie,12);
	ielength=12;
	if((ndisauthmode==Ndis802_11AuthModeWPA)||(ndisauthmode==Ndis802_11AuthModeWPAPSK))
			authmode=_WPA_IE_ID_;
	if((ndisauthmode==Ndis802_11AuthModeWPA2)||(ndisauthmode==Ndis802_11AuthModeWPA2PSK))
			authmode=_WPA2_IE_ID_;

	if(check_fwstate(pmlmepriv, WIFI_UNDER_WPS))
	{
		_rtw_memcpy(out_ie+ielength, psecuritypriv->wps_ie, psecuritypriv->wps_ie_len);
		
		ielength += psecuritypriv->wps_ie_len;
	}
	else if((authmode==_WPA_IE_ID_)||(authmode==_WPA2_IE_ID_))
	{		
		//copy RSN or SSN		
		_rtw_memcpy(&out_ie[ielength], &psecuritypriv->supplicant_ie[0], psecuritypriv->supplicant_ie[1]+2);
		/* debug for CONFIG_IEEE80211W
		{
			int jj;
			printk("supplicant_ie_length=%d &&&&&&&&&&&&&&&&&&&\n", psecuritypriv->supplicant_ie[1]+2);
			for(jj=0; jj < psecuritypriv->supplicant_ie[1]+2; jj++)
				printk(" %02x ", psecuritypriv->supplicant_ie[jj]);
			printk("\n");
		}*/
		ielength+=psecuritypriv->supplicant_ie[1]+2;
		rtw_report_sec_ie(adapter, authmode, psecuritypriv->supplicant_ie);
	
#ifdef CONFIG_DRVEXT_MODULE
		drvext_report_sec_ie(&adapter->drvextpriv, authmode, sec_ie);	
#endif
	}

	iEntry = SecIsInPMKIDList(adapter, pmlmepriv->assoc_bssid);
	if(iEntry<0)
	{
		return ielength;
	}
	else
	{
		if(authmode == _WPA2_IE_ID_)
		{
			ielength=rtw_append_pmkid(adapter, iEntry, out_ie, ielength);
		}
	}

_func_exit_;
	
	return ielength;	
}