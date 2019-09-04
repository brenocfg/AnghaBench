#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_14__ {int signal_strength; int signal_qual; } ;
struct TYPE_13__ {int /*<<< orphan*/  network; } ;
struct TYPE_12__ {TYPE_1__ cur_network; } ;
struct TYPE_16__ {TYPE_2__ recvpriv; TYPE_11__ mlmepriv; } ;
typedef  TYPE_4__ _adapter ;
struct TYPE_15__ {int SignalStrength; int SignalQuality; } ;
struct TYPE_17__ {long Rssi; TYPE_3__ PhyInfo; } ;
typedef  TYPE_5__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_WLAN_BSSID_EX_sz (TYPE_5__*) ; 
 scalar_t__ is_same_network (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static void update_network(WLAN_BSSID_EX *dst, WLAN_BSSID_EX *src,
	_adapter * padapter, bool update_ie)
{
	u8 ss_ori = dst->PhyInfo.SignalStrength;
	u8 sq_ori = dst->PhyInfo.SignalQuality;
	long rssi_ori = dst->Rssi;

	u8 ss_smp = src->PhyInfo.SignalStrength;
	u8 sq_smp = src->PhyInfo.SignalQuality;
	long rssi_smp = src->Rssi;

	u8 ss_final;
	u8 sq_final;
	long rssi_final;

_func_enter_;		

#ifdef CONFIG_ANTENNA_DIVERSITY
	rtw_hal_antdiv_rssi_compared(padapter, dst, src); //this will update src.Rssi, need consider again
#endif

	#if defined(DBG_RX_SIGNAL_DISPLAY_SSID_MONITORED) && 1
	if(strcmp(dst->Ssid.Ssid, DBG_RX_SIGNAL_DISPLAY_SSID_MONITORED) == 0) {
		DBG_871X(FUNC_ADPT_FMT" %s("MAC_FMT", ch%u) ss_ori:%3u, sq_ori:%3u, rssi_ori:%3ld, ss_smp:%3u, sq_smp:%3u, rssi_smp:%3ld\n"
			, FUNC_ADPT_ARG(padapter)
			, src->Ssid.Ssid, MAC_ARG(src->MacAddress), src->Configuration.DSConfig
			,ss_ori, sq_ori, rssi_ori
			,ss_smp, sq_smp, rssi_smp
		);
	}
	#endif

	/* The rule below is 1/5 for sample value, 4/5 for history value */
	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED) && is_same_network(&(padapter->mlmepriv.cur_network.network), src)) {
		/* Take the recvpriv's value for the connected AP*/
		ss_final = padapter->recvpriv.signal_strength;
		sq_final = padapter->recvpriv.signal_qual;
		/* the rssi value here is undecorated, and will be used for antenna diversity */
		if(sq_smp != 101) /* from the right channel */
			rssi_final = (src->Rssi+dst->Rssi*4)/5;
		else
			rssi_final = rssi_ori;
	}
	else {
		if(sq_smp != 101) { /* from the right channel */
			ss_final = ((u32)(src->PhyInfo.SignalStrength)+(u32)(dst->PhyInfo.SignalStrength)*4)/5;
			sq_final = ((u32)(src->PhyInfo.SignalQuality)+(u32)(dst->PhyInfo.SignalQuality)*4)/5;
			rssi_final = (src->Rssi+dst->Rssi*4)/5;
		} else {
			/* bss info not receving from the right channel, use the original RX signal infos */
			ss_final = dst->PhyInfo.SignalStrength;
			sq_final = dst->PhyInfo.SignalQuality;
			rssi_final = dst->Rssi;
		}
		
	}

	if (update_ie)
		_rtw_memcpy((u8 *)dst, (u8 *)src, get_WLAN_BSSID_EX_sz(src));

	dst->PhyInfo.SignalStrength = ss_final;
	dst->PhyInfo.SignalQuality = sq_final;
	dst->Rssi = rssi_final;

	#if defined(DBG_RX_SIGNAL_DISPLAY_SSID_MONITORED) && 1
	if(strcmp(dst->Ssid.Ssid, DBG_RX_SIGNAL_DISPLAY_SSID_MONITORED) == 0) {
		DBG_871X(FUNC_ADPT_FMT" %s("MAC_FMT"), SignalStrength:%u, SignalQuality:%u, RawRSSI:%ld\n"
			, FUNC_ADPT_ARG(padapter)
			, dst->Ssid.Ssid, MAC_ARG(dst->MacAddress), dst->PhyInfo.SignalStrength, dst->PhyInfo.SignalQuality, dst->Rssi);
	}
	#endif

#if 0 // old codes, may be useful one day...
//	DBG_871X("update_network: rssi=0x%lx dst->Rssi=%d ,dst->Rssi=0x%lx , src->Rssi=0x%lx",(dst->Rssi+src->Rssi)/2,dst->Rssi,dst->Rssi,src->Rssi);
	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED) && is_same_network(&(padapter->mlmepriv.cur_network.network), src))
	{
	
		//DBG_871X("b:ssid=%s update_network: src->rssi=0x%d padapter->recvpriv.ui_rssi=%d\n",src->Ssid.Ssid,src->Rssi,padapter->recvpriv.signal);
		if(padapter->recvpriv.signal_qual_data.total_num++ >= PHY_LINKQUALITY_SLID_WIN_MAX)
	        {
	              padapter->recvpriv.signal_qual_data.total_num = PHY_LINKQUALITY_SLID_WIN_MAX;
	              last_evm = padapter->recvpriv.signal_qual_data.elements[padapter->recvpriv.signal_qual_data.index];
	              padapter->recvpriv.signal_qual_data.total_val -= last_evm;
	        }
               	padapter->recvpriv.signal_qual_data.total_val += query_rx_pwr_percentage(src->Rssi);

              	padapter->recvpriv.signal_qual_data.elements[padapter->recvpriv.signal_qual_data.index++] = query_rx_pwr_percentage(src->Rssi);
                if(padapter->recvpriv.signal_qual_data.index >= PHY_LINKQUALITY_SLID_WIN_MAX)
                       padapter->recvpriv.signal_qual_data.index = 0;

		//DBG_871X("Total SQ=%d  pattrib->signal_qual= %d\n", padapter->recvpriv.signal_qual_data.total_val, src->Rssi);

		// <1> Showed on UI for user,in percentage.
		tmpVal = padapter->recvpriv.signal_qual_data.total_val/padapter->recvpriv.signal_qual_data.total_num;
                padapter->recvpriv.signal=(u8)tmpVal;//Link quality

		src->Rssi= translate_percentage_to_dbm(padapter->recvpriv.signal) ;
	}
	else{
//	DBG_871X("ELSE:ssid=%s update_network: src->rssi=0x%d dst->rssi=%d\n",src->Ssid.Ssid,src->Rssi,dst->Rssi);
		src->Rssi=(src->Rssi +dst->Rssi)/2;//dBM
	}	

//	DBG_871X("a:update_network: src->rssi=0x%d padapter->recvpriv.ui_rssi=%d\n",src->Rssi,padapter->recvpriv.signal);

#endif

_func_exit_;		
}