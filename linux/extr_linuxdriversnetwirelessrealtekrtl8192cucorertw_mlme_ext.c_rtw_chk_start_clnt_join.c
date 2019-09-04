#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_priv {unsigned char cur_channel; unsigned char cur_bwmode; unsigned char cur_ch_offset; } ;
struct TYPE_4__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,unsigned char,unsigned char,unsigned char) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int _TRUE ; 
 int /*<<< orphan*/  set_channel_bwmode (TYPE_1__*,unsigned char,unsigned char,unsigned char) ; 

int rtw_chk_start_clnt_join(_adapter *padapter)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	unsigned char	cur_ch = pmlmeext->cur_channel;
	unsigned char	cur_bw = pmlmeext->cur_bwmode;
	unsigned char	cur_ch_offset = pmlmeext->cur_ch_offset;
	bool chbw_allow = _TRUE;
	bool connect_allow = _TRUE;

#ifdef CONFIG_CONCURRENT_MODE
	PADAPTER pbuddy_adapter;	
	struct mlme_ext_priv *pbuddy_mlmeext;
	struct mlme_ext_info	*pbuddy_pmlmeinfo;
	struct mlme_priv *pbuddy_mlmepriv;

	if (!rtw_buddy_adapter_up(padapter)) {
		goto start_join_set_ch_bw;
	}

	pbuddy_adapter = padapter->pbuddy_adapter;		
	pbuddy_mlmeext = &pbuddy_adapter->mlmeextpriv;
	pbuddy_pmlmeinfo = &(pbuddy_mlmeext->mlmext_info);
	pbuddy_mlmepriv = &(pbuddy_adapter->mlmepriv);

	if((pbuddy_pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)//for AP MODE
	{
		DBG_871X("start_clnt_join: "ADPT_FMT"(ch=%d, bw=%d, ch_offset=%d)"
			", "ADPT_FMT" AP mode(ch=%d, bw=%d, ch_offset=%d)\n",
			ADPT_ARG(padapter), pmlmeext->cur_channel, pmlmeext->cur_bwmode, pmlmeext->cur_ch_offset,
			ADPT_ARG(pbuddy_adapter), pbuddy_mlmeext->cur_channel, pbuddy_mlmeext->cur_bwmode, pbuddy_mlmeext->cur_ch_offset);

		if(pmlmeext->cur_channel != pbuddy_mlmeext->cur_channel)
		{
			chbw_allow = _FALSE;
		}
		else if((pmlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40) &&
			(pbuddy_mlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40) &&
			(pmlmeext->cur_ch_offset != pbuddy_mlmeext->cur_ch_offset))
		{
			chbw_allow = _FALSE;
		}
		else if((pmlmeext->cur_bwmode == HT_CHANNEL_WIDTH_20) &&
			(pbuddy_mlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40))
		{
			cur_ch = pmlmeext->cur_channel;
			cur_bw = pbuddy_mlmeext->cur_bwmode;
			cur_ch_offset = pbuddy_mlmeext->cur_ch_offset;
		}

		DBG_871X("start_clnt_join: connect_allow:%d, chbw_allow:%d\n", connect_allow, chbw_allow);
		if (chbw_allow == _FALSE) {
			#ifdef CONFIG_SPCT_CH_SWITCH
			if (1) {
				rtw_ap_inform_ch_switch(pbuddy_adapter, pmlmeext->cur_channel , pmlmeext->cur_ch_offset);
			} else
			#endif
			{
				//issue deauth to all stas if if2 is at ap mode
				rtw_sta_flush(pbuddy_adapter);
			}
			rtw_hal_set_hwreg(padapter, HW_VAR_CHECK_TXBUF, 0);
		}
	}
	else if(check_fwstate(pbuddy_mlmepriv, _FW_LINKED) == _TRUE &&
		check_fwstate(pbuddy_mlmepriv, WIFI_STATION_STATE) == _TRUE) //for Client Mode/p2p client
	{
		DBG_871X("start_clnt_join: "ADPT_FMT"(ch=%d, bw=%d, ch_offset=%d)"
			", "ADPT_FMT" STA mode(ch=%d, bw=%d, ch_offset=%d)\n",
			ADPT_ARG(padapter), pmlmeext->cur_channel, pmlmeext->cur_bwmode, pmlmeext->cur_ch_offset,
			ADPT_ARG(pbuddy_adapter), pbuddy_mlmeext->cur_channel, pbuddy_mlmeext->cur_bwmode, pbuddy_mlmeext->cur_ch_offset);

		if(pmlmeext->cur_channel != pbuddy_mlmeext->cur_channel)
		{
			chbw_allow = _FALSE;
		}
		else if((pmlmeext->cur_bwmode == HT_CHANNEL_WIDTH_20) &&
			(pbuddy_mlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40))
		{
			cur_bw = HT_CHANNEL_WIDTH_40;
			cur_ch_offset = pbuddy_mlmeext->cur_ch_offset;
		}
		else if((pmlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40) &&
			(pbuddy_mlmeext->cur_bwmode == HT_CHANNEL_WIDTH_40) &&
			(pmlmeext->cur_ch_offset != pbuddy_mlmeext->cur_ch_offset))
		{
			chbw_allow = _FALSE;
		}

		connect_allow = chbw_allow;

		#if defined(CONFIG_P2P) && defined(CONFIG_IOCTL_CFG80211)
		/* wlan0-sta mode has higher priority than p2p0-p2p client */
		if (!rtw_p2p_chk_state(&(pbuddy_adapter->wdinfo), P2P_STATE_NONE)
			&& pbuddy_adapter->wdinfo.driver_interface == DRIVER_CFG80211)
		{
			connect_allow = _TRUE;
		}
		#endif /* CONFIG_P2P && CONFIG_IOCTL_CFG80211 */

		DBG_871X("start_clnt_join: connect_allow:%d, chbw_allow:%d\n", connect_allow, chbw_allow);
		if (connect_allow == _TRUE && chbw_allow == _FALSE) {
			/* disconnect buddy's connection */
			rtw_disassoc_cmd(pbuddy_adapter, 500, _FALSE);
			rtw_indicate_disconnect(pbuddy_adapter);
			rtw_free_assoc_resources(pbuddy_adapter, 1);
		}
	}	

start_join_set_ch_bw:
#endif /* CONFIG_CONCURRENT_MODE */

	if (connect_allow == _TRUE) {
		DBG_871X("start_join_set_ch_bw: ch=%d, bwmode=%d, ch_offset=%d\n", cur_ch, cur_bw, cur_ch_offset);
		set_channel_bwmode(padapter, cur_ch, cur_ch_offset, cur_bw);
	}

	return connect_allow == _TRUE ? _SUCCESS : _FAIL;
}