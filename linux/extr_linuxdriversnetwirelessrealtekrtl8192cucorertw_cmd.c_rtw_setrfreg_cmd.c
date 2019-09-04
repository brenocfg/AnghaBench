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
typedef  int /*<<< orphan*/  u32 ;
struct writeRF_parm {int /*<<< orphan*/  value; int /*<<< orphan*/  offset; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetRFReg ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct writeRF_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setrfreg_cmd(_adapter  *padapter, u8 offset, u32 val)
{	
	struct cmd_obj*			ph2c;
	struct writeRF_parm*		pwriterfparm;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;	
	u8	res=_SUCCESS;
_func_enter_;
	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(ph2c==NULL){
		res= _FAIL;	
		goto exit;
	}
	pwriterfparm = (struct writeRF_parm*)rtw_zmalloc(sizeof(struct writeRF_parm)); 

	if(pwriterfparm==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res= _FAIL;
		goto exit;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, pwriterfparm, GEN_CMD_CODE(_SetRFReg));	

	pwriterfparm->offset = offset;
	pwriterfparm->value = val;

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	
exit:
_func_exit_;	
	return res;
}