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
struct cmd_priv {int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  terminate_cmdthread_comp; int /*<<< orphan*/  cmd_queue_comp; } ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

int rtw_init_cmd_priv(struct cmd_priv *pcmdpriv)
{
	init_completion(&pcmdpriv->cmd_queue_comp);
	init_completion(&pcmdpriv->terminate_cmdthread_comp);

	_rtw_init_queue(&pcmdpriv->cmd_queue);
	return _SUCCESS;
}