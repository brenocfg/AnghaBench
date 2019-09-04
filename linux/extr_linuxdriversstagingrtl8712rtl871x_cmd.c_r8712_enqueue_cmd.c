#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cmd_priv {int /*<<< orphan*/  cmd_queue_comp; int /*<<< orphan*/  cmd_queue; TYPE_2__* padapter; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_3__ {scalar_t__ bautoload_fail_flag; } ;
struct TYPE_4__ {TYPE_1__ eeprompriv; } ;

/* Variables and functions */
 int _FAIL ; 
 int _enqueue_cmd (int /*<<< orphan*/ *,struct cmd_obj*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

u32 r8712_enqueue_cmd(struct cmd_priv *pcmdpriv, struct cmd_obj *obj)
{
	int res;

	if (pcmdpriv->padapter->eeprompriv.bautoload_fail_flag)
		return _FAIL;
	res = _enqueue_cmd(&pcmdpriv->cmd_queue, obj);
	complete(&pcmdpriv->cmd_queue_comp);
	return res;
}