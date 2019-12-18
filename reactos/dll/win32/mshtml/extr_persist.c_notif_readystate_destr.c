#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_6__ {TYPE_2__* window; } ;
typedef  TYPE_3__ readystate_task_t ;
struct TYPE_4__ {int /*<<< orphan*/  IHTMLWindow2_iface; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void notif_readystate_destr(task_t *_task)
{
    readystate_task_t *task = (readystate_task_t*)_task;
    IHTMLWindow2_Release(&task->window->base.IHTMLWindow2_iface);
}