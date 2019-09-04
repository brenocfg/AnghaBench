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
typedef  int /*<<< orphan*/  u8 ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct LedBlink_param {int /*<<< orphan*/  pLed; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  PLED_871x ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _LedBlink ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct LedBlink_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_led_blink_cmd(_adapter*padapter, PLED_871x pLed)
{
	struct	cmd_obj*	pcmdobj;
	struct	LedBlink_param *ledBlink_param;
	struct	cmd_priv   *pcmdpriv = &padapter->cmdpriv;

	u8	res=_SUCCESS;

_func_enter_;

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_notice_, ("+rtw_led_blink_cmd\n"));
	
	pcmdobj = (struct	cmd_obj*)rtw_zmalloc(sizeof(struct	cmd_obj));
	if(pcmdobj == NULL){
		res=_FAIL;
		goto exit;
	}

	ledBlink_param = (struct	LedBlink_param *)rtw_zmalloc(sizeof(struct	LedBlink_param));
	if(ledBlink_param == NULL) {
		rtw_mfree((u8 *)pcmdobj, sizeof(struct cmd_obj));
		res= _FAIL;
		goto exit;
	}

	ledBlink_param->pLed=pLed;
	
	init_h2fwcmd_w_parm_no_rsp(pcmdobj, ledBlink_param, GEN_CMD_CODE(_LedBlink));
	res = rtw_enqueue_cmd(pcmdpriv, pcmdobj);
	
exit:

_func_exit_;	

	return res;
}