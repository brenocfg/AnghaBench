#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlme_ext_info {int state; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_channel; struct mlme_ext_info mlmext_info; } ;
struct disconnect_parm {int deauth_timeout_ms; } ;
struct TYPE_13__ {int /*<<< orphan*/  wireless_mode; } ;
struct TYPE_14__ {TYPE_1__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_15__ {int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_3__ WLAN_BSSID_EX ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HW_VAR_BCN_FUNC ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_MLME_DISCONNECT ; 
 int /*<<< orphan*/  Set_MSR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int WIFI_FW_ADHOC_STATE ; 
 int WIFI_FW_AP_STATE ; 
 int WIFI_FW_NULL_STATE ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  _HW_STATE_STATION_ ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_all_cam_entry (TYPE_2__*) ; 
 scalar_t__ is_client_associated_to_ap (TYPE_2__*) ; 
 int /*<<< orphan*/  issue_deauth_ex (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__* null_addr ; 
 int /*<<< orphan*/  rtw_free_uc_swdec_pending_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  set_channel_bwmode (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tx_basic_rate (TYPE_2__*,int /*<<< orphan*/ ) ; 

u8 disconnect_hdl(_adapter *padapter, unsigned char *pbuf)
{
	struct disconnect_parm *param = (struct disconnect_parm *)pbuf;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX		*pnetwork = (WLAN_BSSID_EX*)(&(pmlmeinfo->network));
	u8	val8;

	if (is_client_associated_to_ap(padapter))
	{
		issue_deauth_ex(padapter, pnetwork->MacAddress, WLAN_REASON_DEAUTH_LEAVING, param->deauth_timeout_ms/100, 100);
	}

	//set_opmode_cmd(padapter, infra_client_with_mlme);

	//pmlmeinfo->state = WIFI_FW_NULL_STATE;
	

	rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, 0);
	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

	//restore to initial setting.
	update_tx_basic_rate(padapter, padapter->registrypriv.wireless_mode);

	if(((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE))
	{
		//Stop BCN
		val8 = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_BCN_FUNC, (u8 *)(&val8));
	}


	//set MSR to no link state -> infra. mode
	Set_MSR(padapter, _HW_STATE_STATION_);

	pmlmeinfo->state = WIFI_FW_NULL_STATE;

#ifdef CONFIG_DUALMAC_CONCURRENT
	dc_set_channel_bwmode_disconnect(padapter);
#else
#ifdef CONFIG_CONCURRENT_MODE	
	if((check_buddy_fwstate(padapter, _FW_LINKED)) != _TRUE)
	{
#endif //CONFIG_CONCURRENT_MODE
		//switch to the 20M Hz mode after disconnect
		pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
		pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);
#ifdef CONFIG_CONCURRENT_MODE
	}
#endif //CONFIG_CONCURRENT_MODE
#endif //CONFIG_DUALMAC_CONCURRENT

	flush_all_cam_entry(padapter);
		
	_cancel_timer_ex(&pmlmeext->link_timer);

	rtw_free_uc_swdec_pending_queue(padapter);
	
	return 	H2C_SUCCESS;
}