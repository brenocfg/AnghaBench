#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ length; } ;
union iwreq_data {TYPE_2__ data; } ;
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct TYPE_10__ {scalar_t__ bBusyTraffic; } ;
struct mlme_priv {TYPE_1__ LinkDetectInfo; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_12__ {scalar_t__ hw_init_completed; int /*<<< orphan*/  bup; scalar_t__ bDriverStopped; struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;
struct TYPE_13__ {char SsidLength; int /*<<< orphan*/  Ssid; } ;
typedef  TYPE_4__ NDIS_802_11_SSID ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,scalar_t__) ; 
 int RTW_SSID_SCAN_AMOUNT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  WEXT_CSCAN_ACTV_DWELL_SECTION 133 
#define  WEXT_CSCAN_CHANNEL_SECTION 132 
 int /*<<< orphan*/  WEXT_CSCAN_HEADER ; 
 scalar_t__ WEXT_CSCAN_HEADER_SIZE ; 
#define  WEXT_CSCAN_HOME_DWELL_SECTION 131 
#define  WEXT_CSCAN_PASV_DWELL_SECTION 130 
#define  WEXT_CSCAN_SSID_SECTION 129 
#define  WEXT_CSCAN_TYPE_SECTION 128 
 scalar_t__ _FAIL ; 
 scalar_t__ _FALSE ; 
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ _rtw_memcmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  _rtw_memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  indicate_wx_scan_complete_event (TYPE_3__*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 scalar_t__ rtw_pwr_wakeup (TYPE_3__*) ; 
 scalar_t__ rtw_set_802_11_bssid_list_scan (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static int rtw_wx_set_scan(struct net_device *dev, struct iw_request_info *a,
			     union iwreq_data *wrqu, char *extra)
{
	u8 _status = _FALSE;
	int ret = 0;	
	_adapter *padapter = (_adapter *)rtw_netdev_priv(dev);
	struct mlme_priv *pmlmepriv= &padapter->mlmepriv;
	NDIS_802_11_SSID ssid[RTW_SSID_SCAN_AMOUNT];
	_irqL	irqL;
#ifdef CONFIG_P2P
	struct wifidirect_info *pwdinfo= &(padapter->wdinfo);	
#endif //CONFIG_P2P
	RT_TRACE(_module_rtl871x_mlme_c_,_drv_info_,("rtw_wx_set_scan\n"));

_func_enter_;

	#ifdef DBG_IOCTL
	DBG_871X("DBG_IOCTL %s:%d\n",__FUNCTION__, __LINE__);
	#endif
/*
#ifdef CONFIG_CONCURRENT_MODE
	if(padapter->iface_type > PRIMARY_IFACE)
	{
		ret = -1;
		goto exit;
	}
#endif
*/

#ifdef CONFIG_MP_INCLUDED
	if (check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE)
	{
		ret = -1;
		goto exit;
	}
#endif

	if(_FAIL == rtw_pwr_wakeup(padapter))
	{
		ret= -1;
		goto exit;
	}

	if(padapter->bDriverStopped){
           DBG_871X("bDriverStopped=%d\n", padapter->bDriverStopped);
		ret= -1;
		goto exit;
	}
	
	if(!padapter->bup){
		ret = -1;
		goto exit;
	}
	
	if (padapter->hw_init_completed==_FALSE){
		ret = -1;
		goto exit;
	}

	// When Busy Traffic, driver do not site survey. So driver return success.
	// wpa_supplicant will not issue SIOCSIWSCAN cmd again after scan timeout.
	// modify by thomas 2011-02-22.
	if (pmlmepriv->LinkDetectInfo.bBusyTraffic == _TRUE)
	{
		indicate_wx_scan_complete_event(padapter);
		goto exit;
	} 

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == _TRUE)
	{
		indicate_wx_scan_complete_event(padapter);
		goto exit;
	} 

#ifdef CONFIG_CONCURRENT_MODE
	if (check_buddy_fwstate(padapter,
		_FW_UNDER_SURVEY|_FW_UNDER_LINKING|WIFI_UNDER_WPS) == _TRUE)
	{		
		if(check_buddy_fwstate(padapter, _FW_UNDER_SURVEY))
		{
			printk("scanning_via_buddy_intf\n");
			pmlmepriv->scanning_via_buddy_intf = _TRUE;
		}		

		indicate_wx_scan_complete_event(padapter);
		
		goto exit;
	}
#endif

#ifdef CONFIG_DUALMAC_CONCURRENT
	if (dc_check_fwstate(padapter, _FW_UNDER_SURVEY|_FW_UNDER_LINKING)== _TRUE)
	{
		indicate_wx_scan_complete_event(padapter);
		goto exit;
	}
#endif

//	Mareded by Albert 20101103
//	For the DMP WiFi Display project, the driver won't to scan because
//	the pmlmepriv->scan_interval is always equal to 3.
//	So, the wpa_supplicant won't find out the WPS SoftAP.

/*
	if(pmlmepriv->scan_interval>10)
		pmlmepriv->scan_interval = 0;

	if(pmlmepriv->scan_interval > 0)
	{
		DBG_871X("scan done\n");
		ret = 0;
		goto exit;
	}
		
*/
#ifdef CONFIG_P2P
	if(!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
	{
		rtw_p2p_set_pre_state( pwdinfo, rtw_p2p_state( pwdinfo ) );
		rtw_p2p_set_state(pwdinfo, P2P_STATE_FIND_PHASE_SEARCH);
		rtw_p2p_findphase_ex_set(pwdinfo, P2P_FINDPHASE_EX_FULL);
		rtw_free_network_queue(padapter, _TRUE);
	}
#endif //CONFIG_P2P

	_rtw_memset(ssid, 0, sizeof(NDIS_802_11_SSID)*RTW_SSID_SCAN_AMOUNT);

#if WIRELESS_EXT >= 17
	if (wrqu->data.length == sizeof(struct iw_scan_req)) 
	{
		struct iw_scan_req *req = (struct iw_scan_req *)extra;
	
		if (wrqu->data.flags & IW_SCAN_THIS_ESSID)
		{
			int len = min((int)req->essid_len, IW_ESSID_MAX_SIZE);

			_rtw_memcpy(ssid[0].Ssid, req->essid, len);
			ssid[0].SsidLength = len;	

			DBG_871X("IW_SCAN_THIS_ESSID, ssid=%s, len=%d\n", req->essid, req->essid_len);
		
			_enter_critical_bh(&pmlmepriv->lock, &irqL);				
		
			_status = rtw_sitesurvey_cmd(padapter, ssid, 1, NULL, 0);
		
			_exit_critical_bh(&pmlmepriv->lock, &irqL);
			
		}
		else if (req->scan_type == IW_SCAN_TYPE_PASSIVE)
		{
			DBG_871X("rtw_wx_set_scan, req->scan_type == IW_SCAN_TYPE_PASSIVE\n");
		}
		
	}
	else
#endif

	if(	wrqu->data.length >= WEXT_CSCAN_HEADER_SIZE
		&& _rtw_memcmp(extra, WEXT_CSCAN_HEADER, WEXT_CSCAN_HEADER_SIZE) == _TRUE
	)
	{
		int len = wrqu->data.length -WEXT_CSCAN_HEADER_SIZE;
		char *pos = extra+WEXT_CSCAN_HEADER_SIZE;
		char section;
		char sec_len;
		int ssid_index = 0;

		//DBG_871X("%s COMBO_SCAN header is recognized\n", __FUNCTION__);
		
		while(len >= 1) {
			section = *(pos++); len-=1;

			switch(section) {
				case WEXT_CSCAN_SSID_SECTION:
					//DBG_871X("WEXT_CSCAN_SSID_SECTION\n");
					if(len < 1) {
						len = 0;
						break;
					}
					
					sec_len = *(pos++); len-=1;

					if(sec_len>0 && sec_len<=len) {
						ssid[ssid_index].SsidLength = sec_len;
						_rtw_memcpy(ssid[ssid_index].Ssid, pos, ssid[ssid_index].SsidLength);
						//DBG_871X("%s COMBO_SCAN with specific ssid:%s, %d\n", __FUNCTION__
						//	, ssid[ssid_index].Ssid, ssid[ssid_index].SsidLength);
						ssid_index++;
					}
					
					pos+=sec_len; len-=sec_len;
					break;
					
				
				case WEXT_CSCAN_CHANNEL_SECTION:
					//DBG_871X("WEXT_CSCAN_CHANNEL_SECTION\n");
					pos+=1; len-=1;
					break;
				case WEXT_CSCAN_ACTV_DWELL_SECTION:
					//DBG_871X("WEXT_CSCAN_ACTV_DWELL_SECTION\n");
					pos+=2; len-=2;
					break;
				case WEXT_CSCAN_PASV_DWELL_SECTION:
					//DBG_871X("WEXT_CSCAN_PASV_DWELL_SECTION\n");
					pos+=2; len-=2;					
					break;
				case WEXT_CSCAN_HOME_DWELL_SECTION:
					//DBG_871X("WEXT_CSCAN_HOME_DWELL_SECTION\n");
					pos+=2; len-=2;
					break;
				case WEXT_CSCAN_TYPE_SECTION:
					//DBG_871X("WEXT_CSCAN_TYPE_SECTION\n");
					pos+=1; len-=1;
					break;
				#if 0
				case WEXT_CSCAN_NPROBE_SECTION:
					DBG_871X("WEXT_CSCAN_NPROBE_SECTION\n");
					break;
				#endif
				
				default:
					//DBG_871X("Unknown CSCAN section %c\n", section);
					len = 0; // stop parsing
			}
			//DBG_871X("len:%d\n", len);
			
		}
		
		//jeff: it has still some scan paramater to parse, we only do this now...
		_status = rtw_set_802_11_bssid_list_scan(padapter, ssid, RTW_SSID_SCAN_AMOUNT);
		
	} else
	
	{
		_status = rtw_set_802_11_bssid_list_scan(padapter, NULL, 0);
	}

	if(_status == _FALSE)
		ret = -1;

exit:
	#ifdef DBG_IOCTL
	DBG_871X("DBG_IOCTL %s:%d return %d\n",__FUNCTION__, __LINE__, ret);
	#endif

_func_exit_;

	return ret;	
}