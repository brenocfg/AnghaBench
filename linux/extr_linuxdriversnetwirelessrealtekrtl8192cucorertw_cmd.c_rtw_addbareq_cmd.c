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
struct addBaReq_parm {int /*<<< orphan*/  addr; int /*<<< orphan*/  tid; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _AddBAReq ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct addBaReq_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (unsigned char*,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_addbareq_cmd(_adapter*padapter, u8 tid, u8 *addr)
{
	struct cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj*		ph2c;
	struct addBaReq_parm	*paddbareq_parm;

	u8	res=_SUCCESS;
	
_func_enter_;	

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));	
	if(ph2c==NULL){
		res= _FAIL;
		goto exit;
	}
	
	paddbareq_parm = (struct addBaReq_parm*)rtw_zmalloc(sizeof(struct addBaReq_parm)); 
	if(paddbareq_parm==NULL){
		rtw_mfree((unsigned char *)ph2c, sizeof(struct	cmd_obj));
		res= _FAIL;
		goto exit;
	}

	paddbareq_parm->tid = tid;
	_rtw_memcpy(paddbareq_parm->addr, addr, ETH_ALEN);

	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm, GEN_CMD_CODE(_AddBAReq));

	//DBG_871X("rtw_addbareq_cmd, tid=%d\n", tid);

	//rtw_enqueue_cmd(pcmdpriv, ph2c);	
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	
exit:
	
_func_exit_;

	return res;
}