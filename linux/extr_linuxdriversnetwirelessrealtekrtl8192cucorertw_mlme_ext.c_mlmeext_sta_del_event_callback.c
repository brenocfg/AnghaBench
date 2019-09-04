#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_info {int /*<<< orphan*/  state; } ;
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_channel; struct mlme_ext_info mlmext_info; } ;
struct TYPE_11__ {int /*<<< orphan*/  wireless_mode; } ;
struct TYPE_12__ {TYPE_1__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_MLME_DISCONNECT ; 
 int /*<<< orphan*/  Set_MSR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_FW_NULL_STATE ; 
 int /*<<< orphan*/  _HW_STATE_STATION_ ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_all_cam_entry (TYPE_2__*) ; 
 scalar_t__ is_IBSS_empty (TYPE_2__*) ; 
 scalar_t__ is_client_associated_to_ap (TYPE_2__*) ; 
 int /*<<< orphan*/  null_addr ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_channel_bwmode (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tx_basic_rate (TYPE_2__*,int /*<<< orphan*/ ) ; 

void mlmeext_sta_del_event_callback(_adapter *padapter)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	if (is_client_associated_to_ap(padapter) || is_IBSS_empty(padapter))
	{
		//set_opmode_cmd(padapter, infra_client_with_mlme);

		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, 0);
		rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

		//restore to initial setting.
		update_tx_basic_rate(padapter, padapter->registrypriv.wireless_mode);

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

		//SelectChannel(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset);
		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);
	
#ifdef CONFIG_CONCURRENT_MODE
		}
#endif //CONFIG_CONCURRENT_MODE
#endif //CONFIG_DUALMAC_CONCURRENT

		flush_all_cam_entry(padapter);

		pmlmeinfo->state = WIFI_FW_NULL_STATE;

		//set MSR to no link state -> infra. mode
		Set_MSR(padapter, _HW_STATE_STATION_);

		_cancel_timer_ex(&pmlmeext->link_timer);

	}

}