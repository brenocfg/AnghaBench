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
struct set_stakey_rsp {int dummy; } ;
struct set_assocsta_rsp {int dummy; } ;
struct set_assocsta_parm {int /*<<< orphan*/  addr; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int rspsz; int /*<<< orphan*/ * rsp; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetAssocSta_CMD_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct set_assocsta_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setassocsta_cmd(_adapter  *padapter, u8 *mac_addr)
{
	struct cmd_priv 		*pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj*			ph2c;
	struct set_assocsta_parm	*psetassocsta_para;	
	struct set_stakey_rsp		*psetassocsta_rsp = NULL;

	u8	res=_SUCCESS;

_func_enter_;	

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(ph2c==NULL){
		res= _FAIL;
		goto exit;
	}

	psetassocsta_para = (struct set_assocsta_parm*)rtw_zmalloc(sizeof(struct set_assocsta_parm));
	if(psetassocsta_para==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res=_FAIL;
		goto exit;
	}

	psetassocsta_rsp = (struct set_stakey_rsp*)rtw_zmalloc(sizeof(struct set_assocsta_rsp)); 
	if(psetassocsta_rsp==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		rtw_mfree((u8 *) psetassocsta_para, sizeof(struct set_assocsta_parm));
		return _FAIL;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetassocsta_para, _SetAssocSta_CMD_);
	ph2c->rsp = (u8 *) psetassocsta_rsp;
	ph2c->rspsz = sizeof(struct set_assocsta_rsp);

	_rtw_memcpy(psetassocsta_para->addr, mac_addr,ETH_ALEN);
	
	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	

exit:

_func_exit_;	

	return res;
 }