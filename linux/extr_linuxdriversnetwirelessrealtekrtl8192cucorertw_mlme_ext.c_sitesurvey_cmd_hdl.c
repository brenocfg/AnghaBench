#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct sitesurvey_parm {int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  ch_num; int /*<<< orphan*/  ch; TYPE_1__* ssid; } ;
struct TYPE_16__ {scalar_t__ state; int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  ch; int /*<<< orphan*/  ch_num; TYPE_2__* ssid; scalar_t__ channel_idx; scalar_t__ bss_cnt; } ;
struct mlme_ext_priv {TYPE_3__ sitesurvey_res; } ;
struct TYPE_17__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_4__ _adapter ;
struct TYPE_15__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_14__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNAMIC_FUNC_DISABLE ; 
 int H2C_SUCCESS ; 
 int /*<<< orphan*/  HW_VAR_INITIAL_GAIN ; 
 int /*<<< orphan*/  HW_VAR_MLME_SITESURVEY ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  RTW_CHANNEL_SCAN_AMOUNT ; 
 size_t RTW_SSID_SCAN_AMOUNT ; 
 scalar_t__ SCAN_DISABLE ; 
 scalar_t__ SCAN_PROCESS ; 
 scalar_t__ SCAN_START ; 
 scalar_t__ SCAN_TXNULL ; 
 int /*<<< orphan*/  Save_DM_Func_Flag (TYPE_4__*) ; 
 int /*<<< orphan*/  Set_MSR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Switch_DM_Func (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int _FALSE ; 
 int /*<<< orphan*/  _HW_STATE_NOLINK_ ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_client_associated_to_ap (TYPE_4__*) ; 
 int /*<<< orphan*/  issue_nulldata (TYPE_4__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_scan_ch_decision (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_survey_timer (struct mlme_ext_priv*,int) ; 
 int /*<<< orphan*/  site_survey (TYPE_4__*) ; 

u8 sitesurvey_cmd_hdl(_adapter *padapter, u8 *pbuf)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct sitesurvey_parm	*pparm = (struct sitesurvey_parm *)pbuf;
	u8	bdelayscan = _FALSE;
	u8	val8;
	u32	initialgain;
	u32	i;
	u8	write_initial_gain = 1;

#ifdef CONFIG_P2P
	struct wifidirect_info*	pwdinfo = &padapter->wdinfo;
#endif

	if (pmlmeext->sitesurvey_res.state == SCAN_DISABLE)
	{
#ifdef CONFIG_CONCURRENT_MODE	
		//for first time sitesurvey_cmd
		rtw_hal_set_hwreg(padapter, HW_VAR_CHECK_TXBUF, 0);	
#endif //CONFIG_CONCURRENT_MODE
		
		pmlmeext->sitesurvey_res.state = SCAN_START;
		pmlmeext->sitesurvey_res.bss_cnt = 0;
		pmlmeext->sitesurvey_res.channel_idx = 0;

		for(i=0;i<RTW_SSID_SCAN_AMOUNT;i++){
			if(pparm->ssid[i].SsidLength) {
				_rtw_memcpy(pmlmeext->sitesurvey_res.ssid[i].Ssid, pparm->ssid[i].Ssid, IW_ESSID_MAX_SIZE);
				pmlmeext->sitesurvey_res.ssid[i].SsidLength= pparm->ssid[i].SsidLength;
			} else {
				pmlmeext->sitesurvey_res.ssid[i].SsidLength= 0;
			}
		}

		pmlmeext->sitesurvey_res.ch_num = rtw_scan_ch_decision(padapter
			, pmlmeext->sitesurvey_res.ch, RTW_CHANNEL_SCAN_AMOUNT
			, pparm->ch, pparm->ch_num
		);

		pmlmeext->sitesurvey_res.scan_mode = pparm->scan_mode;

#ifdef CONFIG_DUALMAC_CONCURRENT
		bdelayscan = dc_handle_site_survey(padapter);
#endif

		//issue null data if associating to the AP
		if (is_client_associated_to_ap(padapter) == _TRUE)
		{
			pmlmeext->sitesurvey_res.state = SCAN_TXNULL;

			issue_nulldata(padapter, NULL, 1, 3, 500);

#ifdef CONFIG_CONCURRENT_MODE
			if(is_client_associated_to_ap(padapter->pbuddy_adapter) == _TRUE)
			{
				DBG_871X("adapter is scanning(buddy_adapter is linked), issue nulldata(pwrbit=1)\n");
				
				issue_nulldata(padapter->pbuddy_adapter, NULL, 1, 3, 500);
			}
#endif
			bdelayscan = _TRUE;
		}
#ifdef CONFIG_CONCURRENT_MODE
		else if(is_client_associated_to_ap(padapter->pbuddy_adapter) == _TRUE)
		{
			#ifdef CONFIG_TDLS
			if(padapter->pbuddy_adapter->wdinfo.wfd_tdls_enable == 1)
			{
				issue_tunneled_probe_req(padapter->pbuddy_adapter);
			}
			#endif //CONFIG_TDLS

			pmlmeext->sitesurvey_res.state = SCAN_TXNULL;

			issue_nulldata(padapter->pbuddy_adapter, NULL, 1, 3, 500);

			bdelayscan = _TRUE;			
		}
#endif		
		if(bdelayscan)
		{
			//delay 50ms to protect nulldata(1).
			set_survey_timer(pmlmeext, 50);
			return H2C_SUCCESS;
		}
	}

	if ((pmlmeext->sitesurvey_res.state == SCAN_START) || (pmlmeext->sitesurvey_res.state == SCAN_TXNULL))
	{
#ifdef CONFIG_FIND_BEST_CHANNEL
#if 0
		for (i=0; pmlmeext->channel_set[i].ChannelNum !=0; i++) {
			pmlmeext->channel_set[i].rx_count = 0;				
		}
#endif
#endif /* CONFIG_FIND_BEST_CHANNEL */

		//disable dynamic functions, such as high power, DIG
		Save_DM_Func_Flag(padapter);
		Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, _FALSE);

		//config the initial gain under scaning, need to write the BB registers

#ifdef CONFIG_P2P
#ifdef CONFIG_IOCTL_CFG80211
		if((wdev_to_priv(padapter->rtw_wdev))->p2p_enabled == _TRUE && pwdinfo->driver_interface == DRIVER_CFG80211 )
		{
			write_initial_gain = 0;
		}
		else
#endif //CONFIG_IOCTL_CFG80211
		if ( !rtw_p2p_chk_state( pwdinfo, P2P_STATE_NONE ) )
			initialgain = 0x28;
		else
#endif //CONFIG_P2P
			initialgain = 0x17;

		if(write_initial_gain == 1)
			rtw_hal_set_hwreg(padapter, HW_VAR_INITIAL_GAIN, (u8 *)(&initialgain));

		//set MSR to no link state
		Set_MSR(padapter, _HW_STATE_NOLINK_);

		val8 = 1; //under site survey
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_SITESURVEY, (u8 *)(&val8));

		pmlmeext->sitesurvey_res.state = SCAN_PROCESS;
	}

	site_survey(padapter);

	return H2C_SUCCESS;
	
}