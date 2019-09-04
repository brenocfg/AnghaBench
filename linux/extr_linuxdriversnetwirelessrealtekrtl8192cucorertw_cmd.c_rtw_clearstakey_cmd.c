#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int /*<<< orphan*/  hwaddr; } ;
struct set_stakey_rsp {int dummy; } ;
struct set_stakey_parm {int /*<<< orphan*/  id; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  addr; } ;
struct security_priv {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int rspsz; int /*<<< orphan*/ * rsp; } ;
struct TYPE_4__ {struct security_priv securitypriv; struct mlme_priv mlmepriv; struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetStaKey_CMD_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_cam_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct set_stakey_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_clearstakey_cmd(_adapter *padapter, u8 *psta, u8 entry, u8 enqueue)
{
	struct cmd_obj*			ph2c;
	struct set_stakey_parm	*psetstakey_para;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;
	struct set_stakey_rsp		*psetstakey_rsp = NULL;	
	struct mlme_priv			*pmlmepriv = &padapter->mlmepriv;
	struct security_priv 		*psecuritypriv = &padapter->securitypriv;
	struct sta_info* 			sta = (struct sta_info* )psta;
	u8	res=_SUCCESS;

_func_enter_;

	if(!enqueue)
	{
		clear_cam_entry(padapter, entry);
	}
	else
	{
		ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
		if ( ph2c == NULL){
			res= _FAIL;
			goto exit;
		}

		psetstakey_para = (struct set_stakey_parm*)rtw_zmalloc(sizeof(struct set_stakey_parm));
		if(psetstakey_para==NULL){
			rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
			res=_FAIL;
			goto exit;
		}

		psetstakey_rsp = (struct set_stakey_rsp*)rtw_zmalloc(sizeof(struct set_stakey_rsp)); 
		if(psetstakey_rsp == NULL){
			rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
			rtw_mfree((u8 *) psetstakey_para, sizeof(struct set_stakey_parm));
			res=_FAIL;
			goto exit;
		}

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
		ph2c->rsp = (u8 *) psetstakey_rsp;
		ph2c->rspsz = sizeof(struct set_stakey_rsp);

		_rtw_memcpy(psetstakey_para->addr, sta->hwaddr, ETH_ALEN);

		psetstakey_para->algorithm = _NO_PRIVACY_;

		psetstakey_para->id = entry;
	
		res = rtw_enqueue_cmd(pcmdpriv, ph2c);	
		
	}
	
exit:

_func_exit_;	

	return res;
}