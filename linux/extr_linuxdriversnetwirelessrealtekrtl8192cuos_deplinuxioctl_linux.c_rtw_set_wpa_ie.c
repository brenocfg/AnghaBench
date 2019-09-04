#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned short u16 ;
struct TYPE_5__ {int* supplicant_ie; scalar_t__ dot11PrivacyAlgrthm; int wps_ie_len; int* wps_ie; int /*<<< orphan*/  ndisauthtype; void* ndisencryptstatus; void* dot118021XGrpPrivacy; void* dot11AuthAlgrthm; } ;
struct TYPE_6__ {TYPE_1__ securitypriv; int /*<<< orphan*/  mlmepriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HW_VAR_OFF_RCR_AM ; 
 unsigned short MAX_WPA_IE_LEN ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPA2PSK ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPAPSK ; 
 void* Ndis802_11Encryption1Enabled ; 
 void* Ndis802_11Encryption2Enabled ; 
 void* Ndis802_11Encryption3Enabled ; 
 void* Ndis802_11EncryptionDisabled ; 
 unsigned short RSN_HEADER_LEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_UNDER_WPS ; 
#define  WPA_CIPHER_CCMP 132 
#define  WPA_CIPHER_NONE 131 
#define  WPA_CIPHER_TKIP 130 
#define  WPA_CIPHER_WEP104 129 
#define  WPA_CIPHER_WEP40 128 
 scalar_t__ _AES_ ; 
 void* _NO_PRIVACY_ ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ _TKIP_ ; 
 scalar_t__ _TKIP_WTMIC_ ; 
 scalar_t__ _TRUE ; 
 int _VENDOR_SPECIFIC_IE_ ; 
 void* _WEP104_ ; 
 void* _WEP40_ ; 
 int /*<<< orphan*/  _clr_fwstate_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_os_c ; 
 scalar_t__ _rtw_memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  _rtw_memcpy (int*,...) ; 
 void* dot11AuthAlgrthm_8021X ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_mfree (int*,unsigned short) ; 
 scalar_t__ rtw_parse_wpa2_ie (int*,unsigned short,int*,int*) ; 
 scalar_t__ rtw_parse_wpa_ie (int*,unsigned short,int*,int*) ; 
 int* rtw_zmalloc (unsigned short) ; 
 int /*<<< orphan*/  set_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_set_wpa_ie(_adapter *padapter, char *pie, unsigned short ielen)
{
	u8 *buf=NULL, *pos=NULL;	
	u32 left; 	
	int group_cipher = 0, pairwise_cipher = 0;
	int ret = 0;
	u8	null_addr[]= {0,0,0,0,0,0};
#ifdef CONFIG_P2P
	struct wifidirect_info* pwdinfo = &padapter->wdinfo;
#endif //CONFIG_P2P

	if((ielen > MAX_WPA_IE_LEN) || (pie == NULL)){
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		if(pie == NULL)	
			return ret;
		else
			return -EINVAL;
	}

	if(ielen)
	{		
		buf = rtw_zmalloc(ielen);
		if (buf == NULL){
			ret =  -ENOMEM;
			goto exit;
		}
	
		_rtw_memcpy(buf, pie , ielen);

		//dump
		{
			int i;
			DBG_871X("\n wpa_ie(length:%d):\n", ielen);
			for(i=0;i<ielen;i=i+8)
				DBG_871X("0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x \n",buf[i],buf[i+1],buf[i+2],buf[i+3],buf[i+4],buf[i+5],buf[i+6],buf[i+7]);
		}
	
		pos = buf;
		if(ielen < RSN_HEADER_LEN){
			RT_TRACE(_module_rtl871x_ioctl_os_c,_drv_err_,("Ie len too short %d\n", ielen));
			ret  = -1;
			goto exit;
		}

#if 0
		pos += RSN_HEADER_LEN;
		left  = ielen - RSN_HEADER_LEN;
		
		if (left >= RSN_SELECTOR_LEN){
			pos += RSN_SELECTOR_LEN;
			left -= RSN_SELECTOR_LEN;
		}		
		else if (left > 0){
			RT_TRACE(_module_rtl871x_ioctl_os_c,_drv_err_,("Ie length mismatch, %u too much \n", left));
			ret =-1;
			goto exit;
		}
#endif		
		
		if(rtw_parse_wpa_ie(buf, ielen, &group_cipher, &pairwise_cipher) == _SUCCESS)
		{
			padapter->securitypriv.dot11AuthAlgrthm= dot11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype=Ndis802_11AuthModeWPAPSK;
			_rtw_memcpy(padapter->securitypriv.supplicant_ie, &buf[0], ielen);	
		}
	
		if(rtw_parse_wpa2_ie(buf, ielen, &group_cipher, &pairwise_cipher) == _SUCCESS)
		{
			padapter->securitypriv.dot11AuthAlgrthm= dot11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype=Ndis802_11AuthModeWPA2PSK;	
			_rtw_memcpy(padapter->securitypriv.supplicant_ie, &buf[0], ielen);	
		}
			
		if (group_cipher == 0)
		{
			group_cipher = WPA_CIPHER_NONE;
		}
		if (pairwise_cipher == 0)
		{
			pairwise_cipher = WPA_CIPHER_NONE;
		}
			
		switch(group_cipher)
		{
			case WPA_CIPHER_NONE:
				padapter->securitypriv.dot118021XGrpPrivacy=_NO_PRIVACY_;
				padapter->securitypriv.ndisencryptstatus=Ndis802_11EncryptionDisabled;
				break;
			case WPA_CIPHER_WEP40:
				padapter->securitypriv.dot118021XGrpPrivacy=_WEP40_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
				break;
			case WPA_CIPHER_TKIP:
				padapter->securitypriv.dot118021XGrpPrivacy=_TKIP_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
				break;
			case WPA_CIPHER_CCMP:
				padapter->securitypriv.dot118021XGrpPrivacy=_AES_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
				break;
			case WPA_CIPHER_WEP104:	
				padapter->securitypriv.dot118021XGrpPrivacy=_WEP104_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
				break;
		}

		switch(pairwise_cipher)
		{
			case WPA_CIPHER_NONE:
				padapter->securitypriv.dot11PrivacyAlgrthm=_NO_PRIVACY_;
				padapter->securitypriv.ndisencryptstatus=Ndis802_11EncryptionDisabled;
				break;
			case WPA_CIPHER_WEP40:
				padapter->securitypriv.dot11PrivacyAlgrthm=_WEP40_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
				break;
			case WPA_CIPHER_TKIP:
				padapter->securitypriv.dot11PrivacyAlgrthm=_TKIP_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
				break;
			case WPA_CIPHER_CCMP:
				padapter->securitypriv.dot11PrivacyAlgrthm=_AES_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
				break;
			case WPA_CIPHER_WEP104:	
				padapter->securitypriv.dot11PrivacyAlgrthm=_WEP104_;
				padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
				break;
		}
		
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		{//set wps_ie	
			u16 cnt = 0;	
			u8 eid, wps_oui[4]={0x0,0x50,0xf2,0x04};
			 
			while( cnt < ielen )
			{
				eid = buf[cnt];
		
				if((eid==_VENDOR_SPECIFIC_IE_)&&(_rtw_memcmp(&buf[cnt+2], wps_oui, 4)==_TRUE))
				{
					DBG_871X("SET WPS_IE\n");

					padapter->securitypriv.wps_ie_len = ( (buf[cnt+1]+2) < (MAX_WPA_IE_LEN<<2)) ? (buf[cnt+1]+2):(MAX_WPA_IE_LEN<<2);
					
					_rtw_memcpy(padapter->securitypriv.wps_ie, &buf[cnt], padapter->securitypriv.wps_ie_len);
					
					set_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS);
					
#ifdef CONFIG_P2P
					if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_GONEGO_OK))
					{
						rtw_p2p_set_state(pwdinfo, P2P_STATE_PROVISIONING_ING);
					}
#endif //CONFIG_P2P
					cnt += buf[cnt+1]+2;
					
					break;
				} else {
					cnt += buf[cnt+1]+2; //goto next	
				}				
			}			
		}		
	}

	//TKIP and AES disallow multicast packets until installing group key
	if(padapter->securitypriv.dot11PrivacyAlgrthm == _TKIP_ 
		|| padapter->securitypriv.dot11PrivacyAlgrthm == _TKIP_WTMIC_ 
		|| padapter->securitypriv.dot11PrivacyAlgrthm == _AES_)
		//WPS open need to enable multicast
		//|| check_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS) == _TRUE)
		rtw_hal_set_hwreg(padapter, HW_VAR_OFF_RCR_AM, null_addr);

	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
		 ("rtw_set_wpa_ie: pairwise_cipher=0x%08x padapter->securitypriv.ndisencryptstatus=%d padapter->securitypriv.ndisauthtype=%d\n",
		  pairwise_cipher, padapter->securitypriv.ndisencryptstatus, padapter->securitypriv.ndisauthtype));
 	
exit:

	if (buf) rtw_mfree(buf, ielen);
	
	return ret;	
}