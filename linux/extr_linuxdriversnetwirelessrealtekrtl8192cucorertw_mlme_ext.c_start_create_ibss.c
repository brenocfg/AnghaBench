#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlme_ext_info {int state; int /*<<< orphan*/  bcn_interval; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int cur_channel; struct mlme_ext_info mlmext_info; } ;
struct TYPE_18__ {int* MacAddress; } ;
struct TYPE_19__ {TYPE_2__ dev_network; } ;
struct TYPE_20__ {TYPE_3__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_4__ _adapter ;
struct TYPE_17__ {scalar_t__ DSConfig; } ;
struct TYPE_21__ {TYPE_1__ Configuration; } ;
typedef  TYPE_5__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,unsigned short) ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_MLME_JOIN ; 
 int /*<<< orphan*/  HW_VAR_SEC_CFG ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Set_MSR (TYPE_4__*,int) ; 
 int WIFI_FW_ADHOC_STATE ; 
 int WIFI_FW_ASSOC_SUCCESS ; 
 int WIFI_FW_NULL_STATE ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  beacon_timing_control (TYPE_4__*) ; 
 unsigned short cap_IBSS ; 
 int /*<<< orphan*/  get_beacon_interval (TYPE_5__*) ; 
 int /*<<< orphan*/  report_join_res (TYPE_4__*,int) ; 
 unsigned short rtw_get_capability (TYPE_5__*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ send_beacon (TYPE_4__*) ; 
 int /*<<< orphan*/  set_channel_bwmode (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_capinfo (TYPE_4__*,unsigned short) ; 
 int /*<<< orphan*/  update_wireless_mode (TYPE_4__*) ; 

void start_create_ibss(_adapter* padapter)
{
	unsigned short	caps;
	u8	val8;
	u8	join_type;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX		*pnetwork = (WLAN_BSSID_EX*)(&(pmlmeinfo->network));
	pmlmeext->cur_channel = (u8)pnetwork->Configuration.DSConfig;
	pmlmeinfo->bcn_interval = get_beacon_interval(pnetwork);

	//update wireless mode
	update_wireless_mode(padapter);

	//udpate capability
	caps = rtw_get_capability((WLAN_BSSID_EX *)pnetwork);
	update_capinfo(padapter, caps);
	if(caps&cap_IBSS)//adhoc master
	{
		//set_opmode_cmd(padapter, adhoc);//removed

		val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		//switch channel
		//SelectChannel(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE);
		set_channel_bwmode(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HT_CHANNEL_WIDTH_20);

		beacon_timing_control(padapter);

		//set msr to WIFI_FW_ADHOC_STATE
		pmlmeinfo->state = WIFI_FW_ADHOC_STATE;
		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		//issue beacon
		if(send_beacon(padapter)==_FAIL)
		{
			RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("issuing beacon frame fail....\n"));

			report_join_res(padapter, -1);
			pmlmeinfo->state = WIFI_FW_NULL_STATE;
		}
		else
		{
			rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, padapter->registrypriv.dev_network.MacAddress);
			join_type = 0;
			rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

			report_join_res(padapter, 1);
			pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;
		}
	}
	else
	{
		DBG_871X("start_create_ibss, invalid cap:%x\n", caps);
		return;
	}

}