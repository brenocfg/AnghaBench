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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct cmd_priv {scalar_t__ rsp_allocated_buf; scalar_t__ cmd_allocated_buf; int /*<<< orphan*/  terminate_cmdthread_sema; int /*<<< orphan*/  cmd_queue_sema; TYPE_1__ cmd_queue; } ;

/* Variables and functions */
 scalar_t__ CMDBUFF_ALIGN_SZ ; 
 scalar_t__ MAX_CMDSZ ; 
 scalar_t__ MAX_RSPSZ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_free_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_spinlock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__,scalar_t__) ; 

void _rtw_free_cmd_priv (struct	cmd_priv *pcmdpriv)
{
_func_enter_;

	if(pcmdpriv){
		_rtw_spinlock_free(&(pcmdpriv->cmd_queue.lock));
		_rtw_free_sema(&(pcmdpriv->cmd_queue_sema));
		//_rtw_free_sema(&(pcmdpriv->cmd_done_sema));
		_rtw_free_sema(&(pcmdpriv->terminate_cmdthread_sema));

		if (pcmdpriv->cmd_allocated_buf)
			rtw_mfree(pcmdpriv->cmd_allocated_buf, MAX_CMDSZ + CMDBUFF_ALIGN_SZ);
		
		if (pcmdpriv->rsp_allocated_buf)
			rtw_mfree(pcmdpriv->rsp_allocated_buf, MAX_RSPSZ + 4);
	}
_func_exit_;		
}