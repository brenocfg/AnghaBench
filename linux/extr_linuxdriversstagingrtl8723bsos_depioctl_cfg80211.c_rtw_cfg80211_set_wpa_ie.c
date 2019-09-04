#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ dot11PrivacyAlgrthm; size_t wps_ie_len; int /*<<< orphan*/  ndisauthtype; void* ndisencryptstatus; int /*<<< orphan*/ * wps_ie; void* dot118021XGrpPrivacy; int /*<<< orphan*/ * supplicant_ie; void* dot11AuthAlgrthm; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; TYPE_1__ securitypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,size_t,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HW_VAR_OFF_RCR_AM ; 
 size_t MAX_P2P_IE_LEN ; 
 size_t MAX_WPA_IE_LEN ; 
 size_t MAX_WPS_IE_LEN ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPA2PSK ; 
 int /*<<< orphan*/  Ndis802_11AuthModeWPAPSK ; 
 void* Ndis802_11Encryption1Enabled ; 
 void* Ndis802_11Encryption2Enabled ; 
 void* Ndis802_11Encryption3Enabled ; 
 void* Ndis802_11EncryptionDisabled ; 
 size_t RSN_HEADER_LEN ; 
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
 void* _WEP104_ ; 
 void* _WEP40_ ; 
 int /*<<< orphan*/  _clr_fwstate_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_os_c ; 
 void* dot11AuthAlgrthm_8021X ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rtw_get_wpa2_ie (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/ * rtw_get_wpa_ie (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/ * rtw_get_wps_ie (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_parse_wpa2_ie (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ rtw_parse_wpa_ie (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtw_zmalloc (size_t) ; 
 int /*<<< orphan*/  set_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtw_cfg80211_set_wpa_ie(struct adapter *padapter, u8 *pie, size_t ielen)
{
	u8 *buf = NULL, *pos = NULL;
	int group_cipher = 0, pairwise_cipher = 0;
	int ret = 0;
	int wpa_ielen = 0;
	int wpa2_ielen = 0;
	u8 *pwpa, *pwpa2;
	u8 null_addr[]= {0, 0, 0, 0, 0, 0};

	if (pie == NULL || !ielen) {
		/* Treat this as normal case, but need to clear WIFI_UNDER_WPS */
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		goto exit;
	}

	if (ielen > MAX_WPA_IE_LEN+MAX_WPS_IE_LEN+MAX_P2P_IE_LEN) {
		ret = -EINVAL;
		goto exit;
	}

	buf = rtw_zmalloc(ielen);
	if (buf == NULL) {
		ret =  -ENOMEM;
		goto exit;
	}

	memcpy(buf, pie , ielen);

	/* dump */
	{
		int i;
		DBG_8192C("set wpa_ie(length:%zu):\n", ielen);
		for (i = 0;i<ielen;i =i+8)
			DBG_8192C("0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x\n", buf[i], buf[i+1], buf[i+2], buf[i+3], buf[i+4], buf[i+5], buf[i+6], buf[i+7]);
	}

	pos = buf;
	if (ielen < RSN_HEADER_LEN) {
		RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_err_, ("Ie len too short %d\n", ielen));
		ret  = -1;
		goto exit;
	}

	pwpa = rtw_get_wpa_ie(buf, &wpa_ielen, ielen);
	if (pwpa && wpa_ielen>0)
	{
		if (rtw_parse_wpa_ie(pwpa, wpa_ielen+2, &group_cipher, &pairwise_cipher, NULL) == _SUCCESS)
		{
			padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype =Ndis802_11AuthModeWPAPSK;
			memcpy(padapter->securitypriv.supplicant_ie, &pwpa[0], wpa_ielen+2);

			DBG_8192C("got wpa_ie, wpa_ielen:%u\n", wpa_ielen);
		}
	}

	pwpa2 = rtw_get_wpa2_ie(buf, &wpa2_ielen, ielen);
	if (pwpa2 && wpa2_ielen>0)
	{
		if (rtw_parse_wpa2_ie(pwpa2, wpa2_ielen+2, &group_cipher, &pairwise_cipher, NULL) == _SUCCESS)
		{
			padapter->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_8021X;
			padapter->securitypriv.ndisauthtype =Ndis802_11AuthModeWPA2PSK;
			memcpy(padapter->securitypriv.supplicant_ie, &pwpa2[0], wpa2_ielen+2);

			DBG_8192C("got wpa2_ie, wpa2_ielen:%u\n", wpa2_ielen);
		}
	}

	if (group_cipher == 0)
	{
		group_cipher = WPA_CIPHER_NONE;
	}
	if (pairwise_cipher == 0)
	{
		pairwise_cipher = WPA_CIPHER_NONE;
	}

	switch (group_cipher)
	{
		case WPA_CIPHER_NONE:
			padapter->securitypriv.dot118021XGrpPrivacy = _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus =Ndis802_11EncryptionDisabled;
			break;
		case WPA_CIPHER_WEP40:
			padapter->securitypriv.dot118021XGrpPrivacy = _WEP40_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			break;
		case WPA_CIPHER_TKIP:
			padapter->securitypriv.dot118021XGrpPrivacy = _TKIP_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			break;
		case WPA_CIPHER_CCMP:
			padapter->securitypriv.dot118021XGrpPrivacy = _AES_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			break;
		case WPA_CIPHER_WEP104:
			padapter->securitypriv.dot118021XGrpPrivacy = _WEP104_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			break;
	}

	switch (pairwise_cipher)
	{
		case WPA_CIPHER_NONE:
			padapter->securitypriv.dot11PrivacyAlgrthm = _NO_PRIVACY_;
			padapter->securitypriv.ndisencryptstatus =Ndis802_11EncryptionDisabled;
			break;
		case WPA_CIPHER_WEP40:
			padapter->securitypriv.dot11PrivacyAlgrthm = _WEP40_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			break;
		case WPA_CIPHER_TKIP:
			padapter->securitypriv.dot11PrivacyAlgrthm = _TKIP_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption2Enabled;
			break;
		case WPA_CIPHER_CCMP:
			padapter->securitypriv.dot11PrivacyAlgrthm = _AES_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption3Enabled;
			break;
		case WPA_CIPHER_WEP104:
			padapter->securitypriv.dot11PrivacyAlgrthm = _WEP104_;
			padapter->securitypriv.ndisencryptstatus = Ndis802_11Encryption1Enabled;
			break;
	}

	{/* handle wps_ie */
		uint wps_ielen;
		u8 *wps_ie;

		wps_ie = rtw_get_wps_ie(buf, ielen, NULL, &wps_ielen);
		if (wps_ie && wps_ielen > 0) {
			DBG_8192C("got wps_ie, wps_ielen:%u\n", wps_ielen);
			padapter->securitypriv.wps_ie_len = wps_ielen<MAX_WPS_IE_LEN?wps_ielen:MAX_WPS_IE_LEN;
			memcpy(padapter->securitypriv.wps_ie, wps_ie, padapter->securitypriv.wps_ie_len);
			set_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS);
		} else {
			_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
		}
	}

	/* TKIP and AES disallow multicast packets until installing group key */
	if (padapter->securitypriv.dot11PrivacyAlgrthm == _TKIP_
		|| padapter->securitypriv.dot11PrivacyAlgrthm == _TKIP_WTMIC_
		|| padapter->securitypriv.dot11PrivacyAlgrthm == _AES_)
		/* WPS open need to enable multicast */
		/*  check_fwstate(&padapter->mlmepriv, WIFI_UNDER_WPS) == true) */
		rtw_hal_set_hwreg(padapter, HW_VAR_OFF_RCR_AM, null_addr);

	RT_TRACE(_module_rtl871x_ioctl_os_c, _drv_info_,
		("rtw_set_wpa_ie: pairwise_cipher = 0x%08x padapter->securitypriv.ndisencryptstatus =%d padapter->securitypriv.ndisauthtype =%d\n",
		pairwise_cipher, padapter->securitypriv.ndisencryptstatus, padapter->securitypriv.ndisauthtype));

exit:
	kfree(buf);
	if (ret)
		_clr_fwstate_(&padapter->mlmepriv, WIFI_UNDER_WPS);
	return ret;
}