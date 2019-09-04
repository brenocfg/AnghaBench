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
struct setphy_parm {void* rfchannel; void* modem; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {struct cmd_priv cmdpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* _FAIL ; 
 void* _SUCCESS ; 
 int /*<<< orphan*/  _SetPhy_CMD_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct setphy_parm*,int /*<<< orphan*/ ) ; 
 void* rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (void**,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

u8 rtw_setphy_cmd(_adapter *padapter, u8 modem, u8 ch)
{
	struct cmd_obj*			ph2c;
	struct setphy_parm*		psetphypara;
	struct cmd_priv 			*pcmdpriv=&padapter->cmdpriv;
//	struct mlme_priv			*pmlmepriv = &padapter->mlmepriv;
//	struct registry_priv*		pregistry_priv = &padapter->registrypriv;
	u8	res=_SUCCESS;

_func_enter_;	

	ph2c = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj));
	if(ph2c==NULL){
		res= _FAIL;
		goto exit;
		}
	psetphypara = (struct setphy_parm*)rtw_zmalloc(sizeof(struct setphy_parm)); 

	if(psetphypara==NULL){
		rtw_mfree((u8 *) ph2c, sizeof(struct	cmd_obj));
		res= _FAIL;
		goto exit;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetphypara, _SetPhy_CMD_);

	RT_TRACE(_module_rtl871x_cmd_c_,_drv_info_,("CH=%d, modem=%d", ch, modem));

	psetphypara->modem = modem;
	psetphypara->rfchannel = ch;

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);	
exit:	
_func_exit_;		
	return res;
}