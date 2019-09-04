#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int qos; int /*<<< orphan*/  order; int /*<<< orphan*/  privacy; int /*<<< orphan*/  mdata; int /*<<< orphan*/  mfrag; int /*<<< orphan*/  pw_save; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  frag_num; int /*<<< orphan*/  to_fr_ds; } ;
struct TYPE_9__ {scalar_t__* rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  scalar_t__ u8 ;
struct recv_priv {int /*<<< orphan*/  rx_drop; } ;
typedef  int /*<<< orphan*/  sint ;
struct TYPE_11__ {struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int /*<<< orphan*/  GetFragNum (scalar_t__*) ; 
 scalar_t__ GetFrameSubType (scalar_t__*) ; 
 scalar_t__ GetFrameType (scalar_t__*) ; 
 int /*<<< orphan*/  GetMData (scalar_t__*) ; 
 int /*<<< orphan*/  GetMFrag (scalar_t__*) ; 
 int /*<<< orphan*/  GetOrder (scalar_t__*) ; 
 int /*<<< orphan*/  GetPrivacy (scalar_t__*) ; 
 int /*<<< orphan*/  GetPwrMgt (scalar_t__*) ; 
 int /*<<< orphan*/  GetSequence (scalar_t__*) ; 
 int /*<<< orphan*/  LED_CTL_RX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  WIFI_CTRL_TYPE 130 
#define  WIFI_DATA_TYPE 129 
#define  WIFI_MGT_TYPE 128 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  get_tofr_ds (scalar_t__*) ; 
 int /*<<< orphan*/  rtw_led_control (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_recv_ctrl_frame (TYPE_3__*,union recv_frame*) ; 
 int /*<<< orphan*/  validate_recv_data_frame (TYPE_3__*,union recv_frame*) ; 
 int /*<<< orphan*/  validate_recv_mgnt_frame (TYPE_3__*,union recv_frame*) ; 

sint validate_recv_frame(_adapter *adapter, union recv_frame *precv_frame)
{
	//shall check frame subtype, to / from ds, da, bssid

	//then call check if rx seq/frag. duplicated.

	u8 type;
	u8 subtype;
	sint retval = _SUCCESS;

	struct rx_pkt_attrib *pattrib = & precv_frame->u.hdr.attrib;

	u8 *ptr = precv_frame->u.hdr.rx_data;
	u8  ver =(unsigned char) (*ptr)&0x3 ;
#ifdef CONFIG_FIND_BEST_CHANNEL
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
#endif

#ifdef CONFIG_TDLS
	struct tdls_info *ptdlsinfo = &adapter->tdlsinfo;
#endif //CONFIG_TDLS

_func_enter_;


#ifdef CONFIG_FIND_BEST_CHANNEL
	if (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) {
		int ch_set_idx = rtw_ch_set_search_ch(pmlmeext->channel_set, rtw_get_oper_ch(adapter));
		if (ch_set_idx >= 0)
			pmlmeext->channel_set[ch_set_idx].rx_count++;
	}
#endif

#ifdef CONFIG_TDLS
	if(ptdlsinfo->ch_sensing==1 && ptdlsinfo->cur_channel !=0){
		ptdlsinfo->collect_pkt_num[ptdlsinfo->cur_channel-1]++;
	}
#endif //CONFIG_TDLS

#ifdef RTK_DMP_PLATFORM
	if ( 0 )
	{
		DBG_871X("++\n");
		{
			int i;
			for(i=0; i<64;i=i+8)
				DBG_871X("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:", *(ptr+i),
				*(ptr+i+1), *(ptr+i+2) ,*(ptr+i+3) ,*(ptr+i+4),*(ptr+i+5), *(ptr+i+6), *(ptr+i+7));

		}
		DBG_871X("--\n");
	}
#endif //RTK_DMP_PLATFORM

	//add version chk
	if(ver!=0){
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("validate_recv_data_frame fail! (ver!=0)\n"));
		retval= _FAIL;
		goto exit;
	}

	type =  GetFrameType(ptr);
	subtype = GetFrameSubType(ptr); //bit(7)~bit(2)

	pattrib->to_fr_ds = get_tofr_ds(ptr);

	pattrib->frag_num = GetFragNum(ptr);
	pattrib->seq_num = GetSequence(ptr);

	pattrib->pw_save = GetPwrMgt(ptr);
	pattrib->mfrag = GetMFrag(ptr);
	pattrib->mdata = GetMData(ptr);
	pattrib->privacy = GetPrivacy(ptr);
	pattrib->order = GetOrder(ptr);
#if 0 //for debug

if(pHalData->bDumpRxPkt ==1){
	int i;
	DBG_871X("############################# \n");
	
	for(i=0; i<64;i=i+8)
		DBG_871X("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:\n", *(ptr+i),
		*(ptr+i+1), *(ptr+i+2) ,*(ptr+i+3) ,*(ptr+i+4),*(ptr+i+5), *(ptr+i+6), *(ptr+i+7));
	DBG_871X("############################# \n");
}
else if(pHalData->bDumpRxPkt ==2){
	if(type== WIFI_MGT_TYPE){
		int i;
		DBG_871X("############################# \n");

		for(i=0; i<64;i=i+8)
			DBG_871X("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:\n", *(ptr+i),
			*(ptr+i+1), *(ptr+i+2) ,*(ptr+i+3) ,*(ptr+i+4),*(ptr+i+5), *(ptr+i+6), *(ptr+i+7));
		DBG_871X("############################# \n");
	}
}
else if(pHalData->bDumpRxPkt ==3){
	if(type== WIFI_DATA_TYPE){
		int i;
		DBG_871X("############################# \n");
		
		for(i=0; i<64;i=i+8)
			DBG_871X("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:\n", *(ptr+i),
			*(ptr+i+1), *(ptr+i+2) ,*(ptr+i+3) ,*(ptr+i+4),*(ptr+i+5), *(ptr+i+6), *(ptr+i+7));
		DBG_871X("############################# \n");
	}
}

#endif
	switch (type)
	{
		case WIFI_MGT_TYPE: //mgnt
#ifdef CONFIG_IEEE80211W
			if(validate_80211w_mgmt(adapter, precv_frame) == _FAIL)
			{
				retval = _FAIL;
				break;
			}
#endif //CONFIG_IEEE80211W
			
			retval = validate_recv_mgnt_frame(adapter, precv_frame);
			if (retval == _FAIL)
			{
				RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("validate_recv_mgnt_frame fail\n"));
			}
			retval = _FAIL; // only data frame return _SUCCESS
			break;
		case WIFI_CTRL_TYPE: //ctrl
			retval = validate_recv_ctrl_frame(adapter, precv_frame);
			if (retval == _FAIL)
			{
				RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("validate_recv_ctrl_frame fail\n"));
			}
			retval = _FAIL; // only data frame return _SUCCESS
			break;
		case WIFI_DATA_TYPE: //data
			rtw_led_control(adapter, LED_CTL_RX);
			pattrib->qos = (subtype & BIT(7))? 1:0;
			retval = validate_recv_data_frame(adapter, precv_frame);
			if (retval == _FAIL)
			{
				struct recv_priv *precvpriv = &adapter->recvpriv;
				RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("validate_recv_data_frame fail\n"));
				precvpriv->rx_drop++;
			}
			break;
		default:
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("validate_recv_data_frame fail! type=0x%x\n", type));
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME validate_recv_data_frame fail! type=0x%x\n", type);
			#endif
			retval = _FAIL;
			break;
	}

exit:

_func_exit_;

	return retval;
}