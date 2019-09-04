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
struct drvextra_cmd_parm {int ec_id; scalar_t__ type_size; scalar_t__ pbuf; } ;
struct c2h_evt_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
#define  C2H_WK_CID 133 
#define  DYNAMIC_CHK_WK_CID 132 
#define  FREE_ASSOC_RESOURCES 131 
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
#define  P2P_PROTO_WK_CID 130 
#define  POWER_SAVING_CTRL_WK_CID 129 
#define  RESET_SECURITYPRIV 128 
 int /*<<< orphan*/  c2h_evt_hdl (int /*<<< orphan*/ *,struct c2h_evt_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dynamic_chk_wk_hdl (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_assoc_resources_hdl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_protocol_wk_hdl (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  power_saving_wk_hdl (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reset_securitypriv_hdl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__,scalar_t__) ; 

u8 rtw_drvextra_cmd_hdl(_adapter *padapter, unsigned char *pbuf)
{
	struct drvextra_cmd_parm *pdrvextra_cmd;

	if(!pbuf)
		return H2C_PARAMETERS_ERROR;

	pdrvextra_cmd = (struct drvextra_cmd_parm*)pbuf;
	
	switch(pdrvextra_cmd->ec_id)
	{
		case DYNAMIC_CHK_WK_CID:
			dynamic_chk_wk_hdl(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type_size);
			break;
		case POWER_SAVING_CTRL_WK_CID:
			power_saving_wk_hdl(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type_size);	
			break;
#ifdef CONFIG_LPS
		case LPS_CTRL_WK_CID:
			lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type_size);
			break;
#endif
#ifdef CONFIG_ANTENNA_DIVERSITY
		case ANT_SELECT_WK_CID:
			antenna_select_wk_hdl(padapter, pdrvextra_cmd->type_size);
			break;
#endif
#ifdef CONFIG_P2P_PS
		case P2P_PS_WK_CID:
			p2p_ps_wk_hdl(padapter, pdrvextra_cmd->type_size);
			break;
#endif // CONFIG_P2P_PS
		case P2P_PROTO_WK_CID:
			//	Commented by Albert 2011/07/01
			//	I used the type_size as the type command
			p2p_protocol_wk_hdl( padapter, pdrvextra_cmd->type_size );
			break;
#ifdef CONFIG_AP_MODE
		case CHECK_HIQ_WK_CID:
			rtw_chk_hi_queue_hdl(padapter);
			break;
#endif //CONFIG_AP_MODE
#ifdef CONFIG_INTEL_WIDI
		case INTEl_WIDI_WK_CID:
			intel_widi_wk_hdl(padapter, pdrvextra_cmd->type_size, pdrvextra_cmd->pbuf);
			break;
#endif //CONFIG_INTEL_WIDI
		//add for CONFIG_IEEE80211W, none 11w can use it
		case RESET_SECURITYPRIV:
			reset_securitypriv_hdl(padapter);
			break;
		case FREE_ASSOC_RESOURCES:
			free_assoc_resources_hdl(padapter);
			break;
		case C2H_WK_CID:
			c2h_evt_hdl(padapter, (struct c2h_evt_hdr *)pdrvextra_cmd->pbuf, NULL);
			break;

		default:
			break;
	}


	if(pdrvextra_cmd->pbuf && pdrvextra_cmd->type_size>0)
	{
		rtw_mfree(pdrvextra_cmd->pbuf, pdrvextra_cmd->type_size);
	}


	return H2C_SUCCESS;

}