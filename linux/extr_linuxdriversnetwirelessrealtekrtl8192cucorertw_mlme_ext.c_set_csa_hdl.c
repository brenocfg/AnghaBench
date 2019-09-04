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

u8 set_csa_hdl(_adapter *padapter, unsigned char *pbuf)
{
#ifdef CONFIG_DFS
	struct SetChannelSwitch_param *setChannelSwitch_param;
	struct SetChannelPlan_param *setChannelPlan_param;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 new_ch_no;
	u8 gval8 = 0x00, sval8 = 0xff;

	if(!pbuf)
		return H2C_PARAMETERS_ERROR;

	setChannelSwitch_param = (struct SetChannelSwitch_param *)pbuf;
	new_ch_no = setChannelSwitch_param->new_ch_no;

	rtw_hal_get_hwreg(padapter, HW_VAR_TXPAUSE, &gval8);

	rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, &sval8);

	DBG_871X("DFS detected! Swiching channel to %d!\n", new_ch_no);
	SelectChannel(padapter, new_ch_no);

	rtw_hal_set_hwreg(padapter, HW_VAR_TXPAUSE, &gval8);

	rtw_free_network_queue(padapter, _TRUE);
	rtw_indicate_disconnect(padapter);

	if ( ((new_ch_no >= 52) && (new_ch_no <= 64)) ||((new_ch_no >= 100) && (new_ch_no <= 140)) ) {
		DBG_871X("Switched to DFS band (ch %02x) again!!\n", new_ch_no);
	}

	return 	H2C_SUCCESS;
#else
	return	H2C_REJECTED;
#endif //CONFIG_DFS

}