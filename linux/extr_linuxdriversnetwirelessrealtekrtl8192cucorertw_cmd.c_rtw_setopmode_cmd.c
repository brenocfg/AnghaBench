#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct setopmode_parm {scalar_t__ mode; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  scalar_t__ NDIS_802_11_NETWORK_INFRASTRUCTURE ;

/* Variables and functions */
 scalar_t__ _FALSE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _SetOpMode_CMD_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct setopmode_parm*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__*,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setopmode_cmd(_adapter  *padapter, NDIS_802_11_NETWORK_INFRASTRUCTURE networktype)
{
	struct	cmd_obj*	ph2c;
	struct	setopmode_parm* psetop;

	struct	cmd_priv   *pcmdpriv= &padapter->cmdpriv;
	u8	res=_SUCCESS;

_func_enter_;

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));			
	if(ph2c==NULL){
		res= _FALSE;
		goto exit;
	}
	psetop = (struct setopmode_parm*)rtw_zmalloc(sizeof(struct setopmode_parm)); 

	if(psetop==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res=_FALSE;
		goto exit;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetop, _SetOpMode_CMD_);
	psetop->mode = (u8)networktype;

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

exit:

_func_exit_;	

	return res;
}