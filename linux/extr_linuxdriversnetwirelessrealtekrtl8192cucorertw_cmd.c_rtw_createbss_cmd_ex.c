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
struct cmd_obj {unsigned char* parmbuf; unsigned int cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CreateBss ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_createbss_cmd_ex(_adapter  *padapter, unsigned char *pbss, unsigned int sz)
{
	struct cmd_obj*	pcmd;
	struct cmd_priv 	*pcmdpriv=&padapter->cmdpriv;
	u8	res=_SUCCESS;
	
_func_enter_;
			
	pcmd = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(pcmd==NULL){
		res= _FAIL;
		goto exit;
	}

	_rtw_init_listhead(&pcmd->list);
	pcmd->cmdcode = GEN_CMD_CODE(_CreateBss);
	pcmd->parmbuf = pbss;
	pcmd->cmdsz =  sz;
	pcmd->rsp = NULL;
	pcmd->rspsz = 0;

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

exit:
	
_func_exit_;	

	return res;	
}