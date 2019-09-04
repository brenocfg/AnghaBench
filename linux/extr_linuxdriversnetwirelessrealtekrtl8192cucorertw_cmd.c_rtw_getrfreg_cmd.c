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
struct readRF_rsp {int dummy; } ;
struct readRF_parm {int /*<<< orphan*/  offset; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {unsigned char* parmbuf; int cmdsz; int rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _GetRFReg ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_getrfreg_cmd(_adapter  *padapter, u8 offset, u8 *pval)
{	
	struct cmd_obj*			ph2c;
	struct readRF_parm*		prdrfparm;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;	
	u8	res=_SUCCESS;

_func_enter_;

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(ph2c==NULL){
		res= _FAIL;
		goto exit;
	}

	prdrfparm = (struct readRF_parm*)rtw_zmalloc(sizeof(struct readRF_parm)); 
	if(prdrfparm ==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res= _FAIL;
		goto exit;
	}

	_rtw_init_listhead(&ph2c->list);
	ph2c->cmdcode =GEN_CMD_CODE(_GetRFReg);
	ph2c->parmbuf = (unsigned char *)prdrfparm;
	ph2c->cmdsz =  sizeof(struct readRF_parm);
	ph2c->rsp = pval;
	ph2c->rspsz = sizeof(struct readRF_rsp);
	
	prdrfparm ->offset = offset;
	
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	

exit:

_func_exit_;	

	return res;
}