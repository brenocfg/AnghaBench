#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct setopmode_parm {scalar_t__ mode; } ;
struct mlme_ext_info {int state; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {int fw_psmode_iface_id; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  HW_VAR_PORT_SWITCH ; 
 int /*<<< orphan*/  HW_VAR_SET_OPMODE ; 
 int /*<<< orphan*/  LPS_CTRL_CONNECT ; 
 scalar_t__ Ndis802_11APMode ; 
 scalar_t__ Ndis802_11IBSS ; 
 scalar_t__ Ndis802_11Infrastructure ; 
 int WIFI_FW_AP_STATE ; 
 int WIFI_FW_STATION_STATE ; 
 int /*<<< orphan*/  _HW_STATE_ADHOC_ ; 
 int /*<<< orphan*/  _HW_STATE_AP_ ; 
 int /*<<< orphan*/  _HW_STATE_NOLINK_ ; 
 int /*<<< orphan*/  _HW_STATE_STATION_ ; 
 int /*<<< orphan*/  adapter_to_dvobj (struct adapter*) ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 struct adapter* dvobj_get_port0_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_btcoex_MediaStatusNotify (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_lps_ctrl_wk_cmd (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_port_switch_chk (struct adapter*) ; 

u8 setopmode_hdl(struct adapter *padapter, u8 *pbuf)
{
	u8 type;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct setopmode_parm *psetop = (struct setopmode_parm *)pbuf;

	if (psetop->mode == Ndis802_11APMode) {
		pmlmeinfo->state = WIFI_FW_AP_STATE;
		type = _HW_STATE_AP_;
		/* start_ap_mode(padapter); */
	} else if (psetop->mode == Ndis802_11Infrastructure) {
		pmlmeinfo->state &= ~(BIT(0)|BIT(1));/*  clear state */
		pmlmeinfo->state |= WIFI_FW_STATION_STATE;/* set to	STATION_STATE */
		type = _HW_STATE_STATION_;
	} else if (psetop->mode == Ndis802_11IBSS) {
		type = _HW_STATE_ADHOC_;
	} else{
		type = _HW_STATE_NOLINK_;
	}

	rtw_hal_set_hwreg(padapter, HW_VAR_SET_OPMODE, (u8 *)(&type));
	/* Set_NETYPE0_MSR(padapter, type); */


#ifdef CONFIG_AUTO_AP_MODE
	if (psetop->mode == Ndis802_11APMode)
		rtw_auto_ap_start_beacon(padapter);
#endif

	if (rtw_port_switch_chk(padapter)) {
		rtw_hal_set_hwreg(padapter, HW_VAR_PORT_SWITCH, NULL);

		if (psetop->mode == Ndis802_11APMode)
			adapter_to_pwrctl(padapter)->fw_psmode_iface_id = 0xff; /* ap mode won't dowload rsvd pages */
		else if (psetop->mode == Ndis802_11Infrastructure) {
			struct adapter *port0_iface = dvobj_get_port0_adapter(adapter_to_dvobj(padapter));
			if (port0_iface)
				rtw_lps_ctrl_wk_cmd(port0_iface, LPS_CTRL_CONNECT, 0);
		}
	}

	if (psetop->mode == Ndis802_11APMode) {
		/*  Do this after port switch to */
		/*  prevent from downloading rsvd page to wrong port */
		rtw_btcoex_MediaStatusNotify(padapter, 1); /* connect */
	}

	return H2C_SUCCESS;

}