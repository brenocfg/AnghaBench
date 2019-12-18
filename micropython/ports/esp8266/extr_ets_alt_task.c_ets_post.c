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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  os_signal_t ;
typedef  int /*<<< orphan*/  os_param_t ;
struct TYPE_3__ {int /*<<< orphan*/  par; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ os_event_t ;
struct TYPE_4__ {int i_put; int qlen; int i_get; TYPE_1__* queue; } ;

/* Variables and functions */
 int _ets_post (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* emu_tasks ; 
 int /*<<< orphan*/  ets_intr_lock () ; 
 int /*<<< orphan*/  ets_intr_unlock () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int prio2id (int) ; 

bool ets_post(uint8 prio, os_signal_t sig, os_param_t param) {
//    static unsigned cnt; printf("#%d ets_post(%d, %x, %x)\n", cnt++, prio, sig, param);
#if USE_ETS_TASK
    return _ets_post(prio, sig, param);
#else
    ets_intr_lock();

    const int id = prio2id(prio);
    os_event_t *q = emu_tasks[id].queue;
    if (emu_tasks[id].i_put == -1) {
        // queue is full
        printf("ets_post: task %d queue full\n", prio);
        return 1;
    }
    q = &q[emu_tasks[id].i_put++];
    q->sig = sig;
    q->par = param;
    if (emu_tasks[id].i_put == emu_tasks[id].qlen) {
        emu_tasks[id].i_put = 0;
    }
    if (emu_tasks[id].i_put == emu_tasks[id].i_get) {
        // queue got full
        emu_tasks[id].i_put = -1;
    }
    //printf("after ets_post: "); dump_task(prio, &emu_tasks[id]);
    //dump_tasks();

    ets_intr_unlock();

    return 0;
#endif
}