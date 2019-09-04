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
struct cmd_obj {scalar_t__ cmdcode; int cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; scalar_t__ parmbuf; } ;

/* Variables and functions */
 scalar_t__ _CreateBss_CMD_ ; 
 scalar_t__ _JoinBss_CMD_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_mfree (unsigned char*,int) ; 

void rtw_free_cmd_obj(struct cmd_obj *pcmd)
{
_func_enter_;

	if((pcmd->cmdcode!=_JoinBss_CMD_) &&(pcmd->cmdcode!= _CreateBss_CMD_))
	{
		//free parmbuf in cmd_obj
		rtw_mfree((unsigned char*)pcmd->parmbuf, pcmd->cmdsz);
	}	
	
	if(pcmd->rsp!=NULL)
	{
		if(pcmd->rspsz!= 0)
		{
			//free rsp in cmd_obj
			rtw_mfree((unsigned char*)pcmd->rsp, pcmd->rspsz);
		}	
	}	

	//free cmd_obj
	rtw_mfree((unsigned char*)pcmd, sizeof(struct cmd_obj));
	
_func_exit_;		
}