#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlme_priv {int dummy; } ;
struct TYPE_12__ {scalar_t__* MacAddress; } ;
struct mlme_ext_info {int state; TYPE_1__ network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_channel; struct mlme_ext_info mlmext_info; } ;
struct TYPE_13__ {int /*<<< orphan*/  nqos_ssn; } ;
struct TYPE_14__ {TYPE_2__ xmitpriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_MLME_JOIN ; 
 int /*<<< orphan*/  Ndis802_11Infrastructure ; 
 int /*<<< orphan*/  Set_MSR (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mlmeext_joinbss_event_callback (TYPE_3__*,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rtw_setopmode_cmd (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write8 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_channel_bwmode (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sreset_restore_security_station (TYPE_3__*) ; 

void sreset_restore_network_station(_adapter *padapter)
{
	struct mlme_priv *mlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	#if 0
	{
	//=======================================================
	// reset related register of Beacon control

	//set MSR to nolink
	Set_MSR(padapter, _HW_STATE_NOLINK_);		
	// reject all data frame
	rtw_write16(padapter, REG_RXFLTMAP2,0x00);
	//reset TSF
	rtw_write8(padapter, REG_DUAL_TSF_RST, (BIT(0)|BIT(1)));

	// disable update TSF
	SetBcnCtrlReg(padapter, BIT(4), 0);

	//=======================================================
	}
	#endif
	
	rtw_setopmode_cmd(padapter, Ndis802_11Infrastructure);

	{
		u8 threshold;
		#ifdef CONFIG_USB_HCI
		// TH=1 => means that invalidate usb rx aggregation
		// TH=0 => means that validate usb rx aggregation, use init value.
		if(mlmepriv->htpriv.ht_option) {
			if(padapter->registrypriv.wifi_spec==1)		
				threshold = 1;
			else
				threshold = 0;
			rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
		} else {
			threshold = 1;
			rtw_hal_set_hwreg(padapter, HW_VAR_RXDMA_AGG_PG_TH, (u8 *)(&threshold));
		}
		#endif
	}

	set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

	//disable dynamic functions, such as high power, DIG
	//Switch_DM_Func(padapter, DYNAMIC_FUNC_DISABLE, _FALSE);
	
	rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, pmlmeinfo->network.MacAddress);

	{
		u8	join_type = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));
	}

	Set_MSR(padapter, (pmlmeinfo->state & 0x3));

	mlmeext_joinbss_event_callback(padapter, 1);
	//restore Sequence No.
	rtw_write8(padapter,0x4dc,padapter->xmitpriv.nqos_ssn);

	sreset_restore_security_station(padapter);
}