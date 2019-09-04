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
struct rx_pkt_attrib {char* dst; char* src; char* bssid; char* ra; char* ta; } ;
struct TYPE_6__ {char* rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  char u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {int dummy; } ;
typedef  scalar_t__ sint ;
struct TYPE_8__ {int /*<<< orphan*/  eeprompriv; struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 char* GetAddr1Ptr (char*) ; 
 char* GetAddr2Ptr (char*) ; 
 char* GetAddr3Ptr (char*) ; 
 scalar_t__ IS_MCAST (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ _rtw_memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtw_memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 char* get_bssid (struct mlme_priv*) ; 
 char* myid (int /*<<< orphan*/ *) ; 
 struct sta_info* rtw_get_bcmc_stainfo (TYPE_3__*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,char*) ; 

sint sta2sta_data_frame(
	_adapter *adapter,
	union recv_frame *precv_frame,
	struct sta_info**psta
)
{
	u8 *ptr = precv_frame->u.hdr.rx_data;
	sint ret = _SUCCESS;
	struct rx_pkt_attrib *pattrib = & precv_frame->u.hdr.attrib;
	struct	sta_priv 		*pstapriv = &adapter->stapriv;
	struct	mlme_priv	*pmlmepriv = &adapter->mlmepriv;
	u8 *mybssid  = get_bssid(pmlmepriv);
	u8 *myhwaddr = myid(&adapter->eeprompriv);
	u8 * sta_addr = NULL;
	sint bmcast = IS_MCAST(pattrib->dst);

#ifdef CONFIG_TDLS	
	struct tdls_info *ptdlsinfo = &adapter->tdlsinfo;
	struct sta_info *ptdls_sta=NULL;
	u8 *psnap_type=ptr+pattrib->hdrlen + pattrib->iv_len+SNAP_SIZE;
	u8 *pframe_body = psnap_type + ETH_TYPE_LEN + PAYLOAD_TYPE_LEN;
#endif //CONFIG_TDLS

_func_enter_;

	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == _TRUE) ||
		(check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == _TRUE))
	{

		// filter packets that SA is myself or multicast or broadcast
		if (_rtw_memcmp(myhwaddr, pattrib->src, ETH_ALEN)){
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,(" SA==myself \n"));
			ret= _FAIL;
			goto exit;
		}

		if( (!_rtw_memcmp(myhwaddr, pattrib->dst, ETH_ALEN))	&& (!bmcast) ){
			ret= _FAIL;
			goto exit;
		}

		if( _rtw_memcmp(pattrib->bssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		   _rtw_memcmp(mybssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
		   (!_rtw_memcmp(pattrib->bssid, mybssid, ETH_ALEN)) ) {
			ret= _FAIL;
			goto exit;
		}

		sta_addr = pattrib->src;

	}
	else if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) == _TRUE)
	{
#ifdef CONFIG_TDLS
		//direct link data transfer
		if(ptdlsinfo->setup_state == TDLS_LINKED_STATE){
			ptdls_sta = rtw_get_stainfo(pstapriv, pattrib->src);
			if(ptdls_sta==NULL)
			{
				ret=_FAIL;
				goto exit;
			}
			else if(ptdls_sta->tdls_sta_state&TDLS_LINKED_STATE)
			{
				//drop QoS-SubType Data, including QoS NULL, excluding QoS-Data
				if( (GetFrameSubType(ptr) & WIFI_QOS_DATA_TYPE )== WIFI_QOS_DATA_TYPE)
				{
					if(GetFrameSubType(ptr)&(BIT(4)|BIT(5)|BIT(6)))
					{
						DBG_871X("drop QoS-Sybtype Data\n");
						ret= _FAIL;
						goto exit;
					}
				}
				// filter packets that SA is myself or multicast or broadcast
				if (_rtw_memcmp(myhwaddr, pattrib->src, ETH_ALEN)){
					ret= _FAIL;
					goto exit;
				}
				// da should be for me
				if((!_rtw_memcmp(myhwaddr, pattrib->dst, ETH_ALEN))&& (!bmcast))
				{
					ret= _FAIL;
					goto exit;
				}
				// check BSSID
				if( _rtw_memcmp(pattrib->bssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
				     _rtw_memcmp(mybssid, "\x0\x0\x0\x0\x0\x0", ETH_ALEN) ||
				     (!_rtw_memcmp(pattrib->bssid, mybssid, ETH_ALEN)) )
				{
					ret= _FAIL;
					goto exit;
				}

				//process UAPSD tdls sta
				process_pwrbit_data(adapter, precv_frame);

				// if NULL-frame, check pwrbit
				if ((GetFrameSubType(ptr)) == WIFI_DATA_NULL)
				{
					//NULL-frame with pwrbit=1, buffer_STA should buffer frames for sleep_STA
					if(GetPwrMgt(ptr))
					{
						DBG_871X("TDLS: recv peer null frame with pwr bit 1\n");
						ptdls_sta->tdls_sta_state|=TDLS_PEER_SLEEP_STATE;
					}
					// it would be triggered when we are off channel and receiving NULL DATA
					// we can confirm that peer STA is at off channel
					else if(ptdls_sta->tdls_sta_state&TDLS_CH_SWITCH_ON_STATE)
					{
						if((ptdls_sta->tdls_sta_state & TDLS_PEER_AT_OFF_STATE) != TDLS_PEER_AT_OFF_STATE)
						{
							issue_nulldata_to_TDLS_peer_STA(adapter, ptdls_sta, 0);
							ptdls_sta->tdls_sta_state |= TDLS_PEER_AT_OFF_STATE;
							On_TDLS_Peer_Traffic_Rsp(adapter, precv_frame);
						}
					}

					ret= _FAIL;
					goto exit;
				}
				//receive some of all TDLS management frames, process it at ON_TDLS
				if((_rtw_memcmp(psnap_type, SNAP_ETH_TYPE_TDLS, 2))){
					ret= OnTDLS(adapter, precv_frame);
					goto exit;
				}
				
			}

			sta_addr = pattrib->src;
			
		}		
		else
#endif //CONFIG_TDLS
		{
			// For Station mode, sa and bssid should always be BSSID, and DA is my mac-address
			if(!_rtw_memcmp(pattrib->bssid, pattrib->src, ETH_ALEN) )
			{
				RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("bssid != TA under STATION_MODE; drop pkt\n"));
				ret= _FAIL;
				goto exit;
			}

			sta_addr = pattrib->bssid;
		}
	}
	else if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
	{
		if (bmcast)
		{
			// For AP mode, if DA == MCAST, then BSSID should be also MCAST
			if (!IS_MCAST(pattrib->bssid)){
					ret= _FAIL;
					goto exit;
			}
		}
		else // not mc-frame
		{
			// For AP mode, if DA is non-MCAST, then it must be BSSID, and bssid == BSSID
			if(!_rtw_memcmp(pattrib->bssid, pattrib->dst, ETH_ALEN)) {
				ret= _FAIL;
				goto exit;
			}

			sta_addr = pattrib->src;
		}

	}
	else if(check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE)
	{
		_rtw_memcpy(pattrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(pattrib->src, GetAddr2Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(pattrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
		_rtw_memcpy(pattrib->ta, pattrib->src, ETH_ALEN);

		sta_addr = mybssid;
	}
	else
	{
		ret  = _FAIL;
	}



	if(bmcast)
		*psta = rtw_get_bcmc_stainfo(adapter);
	else
		*psta = rtw_get_stainfo(pstapriv, sta_addr); // get ap_info

#ifdef CONFIG_TDLS
	if(ptdls_sta != NULL)
		*psta = ptdls_sta;
#endif //CONFIG_TDLS


	if (*psta == NULL) {
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("can't get psta under sta2sta_data_frame ; drop pkt\n"));
#ifdef CONFIG_MP_INCLUDED
		if(check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE)
		adapter->mppriv.rx_pktloss++;
#endif
		ret= _FAIL;
		goto exit;
	}

exit:
_func_exit_;
	return ret;

}