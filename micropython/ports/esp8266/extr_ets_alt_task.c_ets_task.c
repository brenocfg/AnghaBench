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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  os_task_t ;
typedef  int /*<<< orphan*/  os_event_t ;
struct TYPE_2__ {int qlen; scalar_t__ i_put; scalar_t__ i_get; int /*<<< orphan*/ * queue; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int _ets_task (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* emu_tasks ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int prio2id (int) ; 

bool ets_task(os_task_t task, uint8 prio, os_event_t *queue, uint8 qlen) {
    static unsigned cnt;
    printf("#%d ets_task(%p, %d, %p, %d)\n", cnt++, task, prio, queue, qlen);
#if USE_ETS_TASK
    return _ets_task(task, prio, queue, qlen);
#else
    int id = prio2id(prio);
    emu_tasks[id].task = task;
    emu_tasks[id].queue = queue;
    emu_tasks[id].qlen = qlen;
    emu_tasks[id].i_get = 0;
    emu_tasks[id].i_put = 0;
    return true;
#endif
}