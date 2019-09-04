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
typedef  void* u8 ;
struct writeBB_parm {void* value; void* offset; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 void* _FAIL ; 
 void* _SUCCESS ; 
 int /*<<< orphan*/  _SetBBReg ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct writeBB_parm*,int /*<<< orphan*/ ) ; 
 void* rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (void**,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setbbreg_cmd(_adapter*padapter, u8 offset, u8 val)
{	
	struct cmd_obj*			ph2c;
	struct writeBB_parm*		pwritebbparm;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;	
	u8	res=_SUCCESS;
_func_enter_;
	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(ph2c==NULL){
		res= _FAIL;
		goto exit;
		}
	pwritebbparm = (struct writeBB_parm*)rtw_zmalloc(sizeof(struct writeBB_parm)); 

	if(pwritebbparm==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res= _FAIL;
		goto exit;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, pwritebbparm, GEN_CMD_CODE(_SetBBReg));	

	pwritebbparm->offset = offset;
	pwritebbparm->value = val;

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	
exit:	
_func_exit_;	
	return res;
}