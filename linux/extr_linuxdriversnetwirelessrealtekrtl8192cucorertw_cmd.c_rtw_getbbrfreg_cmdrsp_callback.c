#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cmd_obj {int cmdsz; scalar_t__ parmbuf; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_mfree (unsigned char*,int) ; 

void rtw_getbbrfreg_cmdrsp_callback(_adapter*	padapter,  struct cmd_obj *pcmd)
{       
 _func_enter_;  
		
	//rtw_free_cmd_obj(pcmd);
	rtw_mfree((unsigned char*) pcmd->parmbuf, pcmd->cmdsz);
	rtw_mfree((unsigned char*) pcmd, sizeof(struct cmd_obj));
	
#ifdef CONFIG_MP_INCLUDED	
	padapter->mppriv.workparam.bcompleted= _TRUE;
#endif	
_func_exit_;		
}