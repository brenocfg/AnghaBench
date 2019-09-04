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
struct setratable_parm {int dummy; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetRaTable ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (struct setratable_parm*,struct setratable_parm*,int) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct setratable_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (unsigned char*,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setrttbl_cmd(_adapter  *padapter, struct setratable_parm *prate_table)
{
	struct cmd_obj*			ph2c;
	struct setratable_parm *	psetrttblparm;	
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;
	u8	res=_SUCCESS;
_func_enter_;	

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(ph2c==NULL){
		res= _FAIL;
		goto exit;
		}
	psetrttblparm = (struct setratable_parm*)rtw_zmalloc(sizeof(struct setratable_parm)); 

	if(psetrttblparm==NULL){
		rtw_mfree((unsigned char *) ph2c, sizeof(struct	cmd_obj));
		res= _FAIL;
		goto exit;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetrttblparm, GEN_CMD_CODE(_SetRaTable));

	_rtw_memcpy(psetrttblparm,prate_table,sizeof(struct setratable_parm));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	
exit:
_func_exit_;	
	return res;

}