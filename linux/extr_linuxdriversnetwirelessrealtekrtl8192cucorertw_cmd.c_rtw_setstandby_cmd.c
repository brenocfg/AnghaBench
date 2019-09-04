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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct usb_suspend_parm {int /*<<< orphan*/  action; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetUsbSuspend ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct usb_suspend_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setstandby_cmd(_adapter *padapter, uint action)
{
	struct cmd_obj*			ph2c;
	struct usb_suspend_parm*	psetusbsuspend;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;

	u8 ret = _SUCCESS;
	
_func_enter_;	

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if (ph2c == NULL) {
		ret = _FAIL;
		goto exit;
	}
	
	psetusbsuspend = (struct usb_suspend_parm*)rtw_zmalloc(sizeof(struct usb_suspend_parm)); 
	if (psetusbsuspend == NULL) {
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		ret = _FAIL;
		goto exit;
	}

	psetusbsuspend->action = action;

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetusbsuspend, GEN_CMD_CODE(_SetUsbSuspend));

	ret = rtw_enqueue_cmd(pcmdpriv, ph2c);	
	
exit:	
	
_func_exit_;		

	return ret;
}