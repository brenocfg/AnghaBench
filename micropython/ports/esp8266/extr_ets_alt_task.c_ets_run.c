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

/* Variables and functions */
 int /*<<< orphan*/  _ets_run () ; 
 int /*<<< orphan*/  dump_tasks () ; 
 int /*<<< orphan*/  ets_intr_lock () ; 
 int /*<<< orphan*/  ets_intr_unlock () ; 
 int /*<<< orphan*/  ets_isr_attach (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ets_loop_iter () ; 
 int /*<<< orphan*/  idle_arg ; 
 int /*<<< orphan*/  idle_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_timer_isr ; 
 int /*<<< orphan*/  printf (char*) ; 

bool ets_run(void) {
#if USE_ETS_TASK
    #if SDK_BELOW_1_1_1
    ets_isr_attach(10, my_timer_isr, NULL);
    #endif
    _ets_run();
#else
//    ets_timer_init();
    *(char*)0x3FFFC6FC = 0;
    ets_intr_lock();
    printf("ets_alt_task: ets_run\n");
#if DEBUG
    dump_tasks();
#endif
    ets_intr_unlock();
    while (1) {
        if (!ets_loop_iter()) {
            //printf("idle\n");
            ets_intr_lock();
            if (idle_cb) {
                idle_cb(idle_arg);
            }
            asm("waiti 0");
            ets_intr_unlock();
        }
    }
#endif
}