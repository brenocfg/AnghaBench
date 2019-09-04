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
struct cmd_priv {int /*<<< orphan*/  cmd_queue; } ;
struct cmd_obj {int dummy; } ;

/* Variables and functions */
 struct cmd_obj* _rtw_dequeue_cmd (int /*<<< orphan*/ *) ; 

struct	cmd_obj	*rtw_dequeue_cmd(struct cmd_priv *pcmdpriv)
{
	struct cmd_obj *cmd_obj;

	cmd_obj = _rtw_dequeue_cmd(&pcmdpriv->cmd_queue);

	return cmd_obj;
}