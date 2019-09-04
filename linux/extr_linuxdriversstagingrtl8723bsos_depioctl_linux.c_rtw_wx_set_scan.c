#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; int flags; } ;
union iwreq_data {TYPE_2__ data; } ;
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ndis_802_11_ssid {int SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_3__ {int bBusyTraffic; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_1__ LinkDetectInfo; } ;
struct iw_scan_req {char* essid; scalar_t__ scan_type; scalar_t__ essid_len; } ;
struct iw_request_info {int dummy; } ;
struct adapter {int hw_init_completed; int /*<<< orphan*/  bup; scalar_t__ bDriverStopped; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int IW_SCAN_THIS_ESSID ; 
 scalar_t__ IW_SCAN_TYPE_PASSIVE ; 
 int /*<<< orphan*/  PS_DENY_SCAN ; 
 int RTW_SSID_SCAN_AMOUNT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  WEXT_CSCAN_ACTV_DWELL_SECTION 133 
#define  WEXT_CSCAN_CHANNEL_SECTION 132 
 int /*<<< orphan*/  WEXT_CSCAN_HEADER ; 
 int WEXT_CSCAN_HEADER_SIZE ; 
#define  WEXT_CSCAN_HOME_DWELL_SECTION 131 
#define  WEXT_CSCAN_PASV_DWELL_SECTION 130 
#define  WEXT_CSCAN_SSID_SECTION 129 
#define  WEXT_CSCAN_TYPE_SECTION 128 
 scalar_t__ _FAIL ; 
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  indicate_wx_scan_complete_event (struct adapter*) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct ndis_802_11_ssid*,int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_ps_deny (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_ps_deny_cancel (struct adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_pwr_wakeup (struct adapter*) ; 
 int rtw_set_802_11_bssid_list_scan (struct adapter*,struct ndis_802_11_ssid*,int) ; 
 int rtw_sitesurvey_cmd (struct adapter*,struct ndis_802_11_ssid*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtw_wx_set_scan(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *extra)
{
	u8 _status = false;
	int ret = 0;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ndis_802_11_ssid ssid[RTW_SSID_SCAN_AMOUNT];
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_wx_set_scan\n"));

	#ifdef DBG_IOCTL
	DBG_871X("DBG_IOCTL %s:%d\n", __func__, __LINE__);
	#endif

	rtw_ps_deny(padapter, PS_DENY_SCAN);
	if (_FAIL == rtw_pwr_wakeup(padapter)) {
		ret = -1;
		goto exit;
	}

	if (padapter->bDriverStopped) {
		DBG_871X("bDriverStopped =%d\n", padapter->bDriverStopped);
		ret = -1;
		goto exit;
	}

	if (!padapter->bup) {
		ret = -1;
		goto exit;
	}

	if (padapter->hw_init_completed ==false) {
		ret = -1;
		goto exit;
	}

	/*  When Busy Traffic, driver do not site survey. So driver return success. */
	/*  wpa_supplicant will not issue SIOCSIWSCAN cmd again after scan timeout. */
	/*  modify by thomas 2011-02-22. */
	if (pmlmepriv->LinkDetectInfo.bBusyTraffic == true) {
		indicate_wx_scan_complete_event(padapter);
		goto exit;
	}

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == true) {
		indicate_wx_scan_complete_event(padapter);
		goto exit;
	}

	memset(ssid, 0, sizeof(struct ndis_802_11_ssid)*RTW_SSID_SCAN_AMOUNT);

	if (wrqu->data.length == sizeof(struct iw_scan_req)) {
		struct iw_scan_req *req = (struct iw_scan_req *)extra;

		if (wrqu->data.flags & IW_SCAN_THIS_ESSID) {
			int len = min((int)req->essid_len, IW_ESSID_MAX_SIZE);

			memcpy(ssid[0].Ssid, req->essid, len);
			ssid[0].SsidLength = len;

			DBG_871X("IW_SCAN_THIS_ESSID, ssid =%s, len =%d\n", req->essid, req->essid_len);

			spin_lock_bh(&pmlmepriv->lock);

			_status = rtw_sitesurvey_cmd(padapter, ssid, 1, NULL, 0);

			spin_unlock_bh(&pmlmepriv->lock);

		} else if (req->scan_type == IW_SCAN_TYPE_PASSIVE) {
			DBG_871X("rtw_wx_set_scan, req->scan_type == IW_SCAN_TYPE_PASSIVE\n");
		}

	} else if (wrqu->data.length >= WEXT_CSCAN_HEADER_SIZE
		&& !memcmp(extra, WEXT_CSCAN_HEADER, WEXT_CSCAN_HEADER_SIZE)) {
		int len = wrqu->data.length -WEXT_CSCAN_HEADER_SIZE;
		char *pos = extra+WEXT_CSCAN_HEADER_SIZE;
		char section;
		char sec_len;
		int ssid_index = 0;

		/* DBG_871X("%s COMBO_SCAN header is recognized\n", __func__); */

		while (len >= 1) {
			section = *(pos++); len-= 1;

			switch (section) {
				case WEXT_CSCAN_SSID_SECTION:
					/* DBG_871X("WEXT_CSCAN_SSID_SECTION\n"); */
					if (len < 1) {
						len = 0;
						break;
					}

					sec_len = *(pos++); len-= 1;

					if (sec_len>0 && sec_len<=len) {
						ssid[ssid_index].SsidLength = sec_len;
						memcpy(ssid[ssid_index].Ssid, pos, ssid[ssid_index].SsidLength);
						/* DBG_871X("%s COMBO_SCAN with specific ssid:%s, %d\n", __func__ */
						/* 	, ssid[ssid_index].Ssid, ssid[ssid_index].SsidLength); */
						ssid_index++;
					}

					pos+=sec_len; len-=sec_len;
					break;


				case WEXT_CSCAN_CHANNEL_SECTION:
					/* DBG_871X("WEXT_CSCAN_CHANNEL_SECTION\n"); */
					pos+= 1; len-= 1;
					break;
				case WEXT_CSCAN_ACTV_DWELL_SECTION:
					/* DBG_871X("WEXT_CSCAN_ACTV_DWELL_SECTION\n"); */
					pos+=2; len-=2;
					break;
				case WEXT_CSCAN_PASV_DWELL_SECTION:
					/* DBG_871X("WEXT_CSCAN_PASV_DWELL_SECTION\n"); */
					pos+=2; len-=2;
					break;
				case WEXT_CSCAN_HOME_DWELL_SECTION:
					/* DBG_871X("WEXT_CSCAN_HOME_DWELL_SECTION\n"); */
					pos+=2; len-=2;
					break;
				case WEXT_CSCAN_TYPE_SECTION:
					/* DBG_871X("WEXT_CSCAN_TYPE_SECTION\n"); */
					pos+= 1; len-= 1;
					break;
				default:
					/* DBG_871X("Unknown CSCAN section %c\n", section); */
					len = 0; /*  stop parsing */
			}
			/* DBG_871X("len:%d\n", len); */

		}

		/* jeff: it has still some scan paramater to parse, we only do this now... */
		_status = rtw_set_802_11_bssid_list_scan(padapter, ssid, RTW_SSID_SCAN_AMOUNT);

	} else {
		_status = rtw_set_802_11_bssid_list_scan(padapter, NULL, 0);
	}

	if (_status == false)
		ret = -1;

exit:

	rtw_ps_deny_cancel(padapter, PS_DENY_SCAN);

	#ifdef DBG_IOCTL
	DBG_871X("DBG_IOCTL %s:%d return %d\n", __func__, __LINE__, ret);
	#endif

	return ret;
}