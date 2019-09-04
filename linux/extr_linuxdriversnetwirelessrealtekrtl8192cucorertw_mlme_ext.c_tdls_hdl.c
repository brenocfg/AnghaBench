#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_REJECTED ; 

u8 tdls_hdl(_adapter *padapter, unsigned char *pbuf)
{
#ifdef CONFIG_TDLS
	_irqL irqL;
	struct tdls_info *ptdlsinfo = &padapter->tdlsinfo;
	struct TDLSoption_param *TDLSoption;
	struct sta_info *ptdls_sta;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 survey_channel, i, min, option;

	if(!pbuf)
		return H2C_PARAMETERS_ERROR;

	TDLSoption = (struct TDLSoption_param *)pbuf;

	ptdls_sta = rtw_get_stainfo( &(padapter->stapriv), TDLSoption->addr );
	option = TDLSoption->option;

	if( ptdls_sta == NULL )
	{
		if( option != TDLS_RS_RCR )
			return H2C_REJECTED;
	}

	//_enter_critical_bh(&(ptdlsinfo->hdl_lock), &irqL);
	DBG_871X("[%s] option:%d\n", __FUNCTION__, option);
		
	switch(option){
		case TDLS_WRCR:
			//As long as TDLS handshake success, we should set RCR_CBSSID_DATA bit to 0
			//such we can receive all kinds of data frames.
			rtw_hal_set_hwreg(padapter, HW_VAR_TDLS_WRCR, 0);
			DBG_871X("TDLS with "MAC_FMT"\n", MAC_ARG(ptdls_sta->hwaddr));

			pmlmeinfo->FW_sta_info[ptdls_sta->mac_id].psta = ptdls_sta;
			//set TDLS sta rate.
			set_sta_rate(padapter, ptdls_sta);
			break;
		case TDLS_SD_PTI:
			issue_tdls_peer_traffic_indication(padapter, ptdls_sta);
			break;
		case TDLS_CS_OFF:
			_cancel_timer_ex(&ptdls_sta->base_ch_timer);
			_cancel_timer_ex(&ptdls_sta->off_ch_timer);
			SelectChannel(padapter, pmlmeext->cur_channel);
			ptdls_sta->tdls_sta_state &= ~(TDLS_CH_SWITCH_ON_STATE | 
								TDLS_PEER_AT_OFF_STATE | 
								TDLS_AT_OFF_CH_STATE);
			DBG_871X("go back to base channel\n ");
			issue_nulldata(padapter, NULL, 0, 0, 0);
			break;
		case TDLS_INIT_CH_SEN:
			rtw_hal_set_hwreg(padapter, HW_VAR_TDLS_INIT_CH_SEN, 0);
			pmlmeext->sitesurvey_res.channel_idx = 0;
			ptdls_sta->option = TDLS_DONE_CH_SEN;
			rtw_tdls_cmd(padapter, ptdls_sta->hwaddr, TDLS_DONE_CH_SEN);
			break;
		case TDLS_DONE_CH_SEN:
			survey_channel = pmlmeext->channel_set[pmlmeext->sitesurvey_res.channel_idx].ChannelNum;
			if(survey_channel){
				SelectChannel(padapter, survey_channel);
				ptdlsinfo->cur_channel = survey_channel;
				pmlmeext->sitesurvey_res.channel_idx++;
				_set_timer(&ptdls_sta->option_timer, SURVEY_TO);
			}else{
				SelectChannel(padapter, pmlmeext->cur_channel);

				rtw_hal_set_hwreg(padapter, HW_VAR_TDLS_DONE_CH_SEN, 0);

				if(ptdlsinfo->ch_sensing==1){
					ptdlsinfo->ch_sensing=0;
					ptdlsinfo->cur_channel=1;
					min=ptdlsinfo->collect_pkt_num[0];
					for(i=1; i<MAX_CHANNEL_NUM-1; i++){
						if(min > ptdlsinfo->collect_pkt_num[i]){
							ptdlsinfo->cur_channel=i+1;
							min=ptdlsinfo->collect_pkt_num[i];
						}
						ptdlsinfo->collect_pkt_num[i]=0;
					}
					ptdlsinfo->collect_pkt_num[0]=0;
					ptdlsinfo->candidate_ch=ptdlsinfo->cur_channel;
					DBG_871X("TDLS channel sensing done, candidate channel: %02x\n", ptdlsinfo->candidate_ch);
					ptdlsinfo->cur_channel=0;

				}

				if(ptdls_sta->tdls_sta_state & TDLS_PEER_SLEEP_STATE){
					ptdls_sta->tdls_sta_state |= TDLS_APSD_CHSW_STATE;
				}else{
					//send null data with pwrbit==1 before send ch_switching_req to peer STA.
					issue_nulldata(padapter, NULL, 1, 0, 0);

					ptdls_sta->tdls_sta_state |= TDLS_CH_SW_INITIATOR_STATE;

					issue_tdls_ch_switch_req(padapter, ptdls_sta->hwaddr);
					DBG_871X("issue tdls ch switch req\n");
				}
			}
			break;
		case TDLS_OFF_CH:
			issue_nulldata(padapter, NULL, 1, 0, 0);
			SelectChannel(padapter, ptdls_sta->off_ch);

			DBG_871X("change channel to tar ch:%02x\n", ptdls_sta->off_ch);
			ptdls_sta->tdls_sta_state |= TDLS_AT_OFF_CH_STATE;
			ptdls_sta->tdls_sta_state &= ~(TDLS_PEER_AT_OFF_STATE);
			_set_timer(&ptdls_sta->option_timer, (u32)ptdls_sta->ch_switch_time);
			break;
		case TDLS_BASE_CH:
			_cancel_timer_ex(&ptdls_sta->base_ch_timer);
			_cancel_timer_ex(&ptdls_sta->off_ch_timer);
			SelectChannel(padapter, pmlmeext->cur_channel);
			ptdls_sta->tdls_sta_state &= ~(TDLS_CH_SWITCH_ON_STATE | 
								TDLS_PEER_AT_OFF_STATE | 
								TDLS_AT_OFF_CH_STATE);
			DBG_871X("go back to base channel\n ");
			issue_nulldata(padapter, NULL, 0, 0, 0);
			_set_timer(&ptdls_sta->option_timer, (u32)ptdls_sta->ch_switch_time);
			break;
		case TDLS_P_OFF_CH:
			SelectChannel(padapter, pmlmeext->cur_channel);
			issue_nulldata(padapter, NULL, 0, 0, 0);
			DBG_871X("change channel to base ch:%02x\n", pmlmeext->cur_channel);
			ptdls_sta->tdls_sta_state &= ~(TDLS_PEER_AT_OFF_STATE| TDLS_AT_OFF_CH_STATE);
			_set_timer(&ptdls_sta->off_ch_timer, TDLS_STAY_TIME);
			break;
		case TDLS_P_BASE_CH:
			issue_nulldata(ptdls_sta->padapter, NULL, 1, 0, 0);
			SelectChannel(padapter, ptdls_sta->off_ch);
			DBG_871X("change channel to off ch:%02x\n", ptdls_sta->off_ch);
			ptdls_sta->tdls_sta_state |= TDLS_AT_OFF_CH_STATE;
			if((ptdls_sta->tdls_sta_state & TDLS_PEER_AT_OFF_STATE) != TDLS_PEER_AT_OFF_STATE){
				issue_nulldata_to_TDLS_peer_STA(padapter, ptdls_sta, 0);
			}
			_set_timer(&ptdls_sta->base_ch_timer, TDLS_STAY_TIME);	
			break;
		case TDLS_RS_RCR:
			rtw_hal_set_hwreg(padapter, HW_VAR_TDLS_RS_RCR, 0);
			DBG_871X("wirte REG_RCR, set bit6 on\n");
			break;
		case TDLS_CKALV_PH1:
			_set_timer(&ptdls_sta->alive_timer2, TDLS_ALIVE_TIMER_PH2);
			break;
		case TDLS_CKALV_PH2:
			_set_timer(&ptdls_sta->alive_timer1, TDLS_ALIVE_TIMER_PH1);
			break;
		case TDLS_FREE_STA:
			free_tdls_sta(padapter, ptdls_sta);
			break;
			
	}

	//_exit_critical_bh(&(ptdlsinfo->hdl_lock), &irqL);

	return H2C_SUCCESS;
#else
	return H2C_REJECTED;
#endif //CONFIG_TDLS

}