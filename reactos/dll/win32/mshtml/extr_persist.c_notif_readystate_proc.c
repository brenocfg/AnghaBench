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
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_2__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ readystate_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  notif_readystate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void notif_readystate_proc(task_t *_task)
{
    readystate_task_t *task = (readystate_task_t*)_task;
    notif_readystate(task->window);
}