#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cmd_priv {int /*<<< orphan*/  cmdthd_running; TYPE_1__* padapter; } ;
struct cmd_obj {scalar_t__ cmdcode; } ;
struct TYPE_2__ {int hw_init_completed; } ;

/* Variables and functions */
 scalar_t__ GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _SetChannelPlan ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

int rtw_cmd_filter(struct cmd_priv *pcmdpriv, struct cmd_obj *cmd_obj)
{
	u8 bAllow = false; /* set to true to allow enqueuing cmd when hw_init_completed is false */

	if (cmd_obj->cmdcode == GEN_CMD_CODE(_SetChannelPlan))
		bAllow = true;

	if ((pcmdpriv->padapter->hw_init_completed == false && bAllow == false)
		|| atomic_read(&(pcmdpriv->cmdthd_running)) == false	/* com_thread not running */
	) {
		/* DBG_871X("%s:%s: drop cmdcode:%u, hw_init_completed:%u, cmdthd_running:%u\n", caller_func, __func__, */
		/* 	cmd_obj->cmdcode, */
		/* 	pcmdpriv->padapter->hw_init_completed, */
		/* 	pcmdpriv->cmdthd_running */
		/*  */

		return _FAIL;
	}
	return _SUCCESS;
}