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
typedef  int /*<<< orphan*/  uint32_t ;
struct task_entry {int i_get; int i_put; int qlen; int /*<<< orphan*/ * queue; int /*<<< orphan*/  (* task ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t MP_ARRAY_SIZE (struct task_entry volatile*) ; 
 struct task_entry volatile* emu_tasks ; 
 int /*<<< orphan*/  ets_intr_lock () ; 
 int /*<<< orphan*/  ets_intr_unlock () ; 
 scalar_t__ ets_loop_dont_feed_sw_wdt ; 
 scalar_t__ ets_loop_iter_disable ; 
 int /*<<< orphan*/  idle_arg ; 
 int /*<<< orphan*/  idle_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_soft_wdt_feed () ; 
 int /*<<< orphan*/  system_time_update () ; 

bool ets_loop_iter(void) {
    if (ets_loop_iter_disable) {
        return false;
    }

    // Update 64-bit microsecond counter
    system_time_update();

    // 6 words before pend_flag_noise_check is a variable that is used by
    // the software WDT.  A 1.6 second period timer will increment this
    // variable and if it gets to 2 then the SW WDT will trigger a reset.
    extern uint32_t pend_flag_noise_check;
    uint32_t *sw_wdt = &pend_flag_noise_check - 6;

    //static unsigned cnt;
    bool progress = false;
    for (volatile struct task_entry *t = emu_tasks; t < &emu_tasks[MP_ARRAY_SIZE(emu_tasks)]; t++) {
        if (!ets_loop_dont_feed_sw_wdt) {
            system_soft_wdt_feed();
        }
        ets_intr_lock();
        //printf("etc_loop_iter: "); dump_task(t - emu_tasks + FIRST_PRIO, t);
        if (t->i_get != t->i_put) {
            progress = true;
            //printf("#%d Calling task %d(%p) (%x, %x)\n", cnt++,
            //    t - emu_tasks + FIRST_PRIO, t->task, t->queue[t->i_get].sig, t->queue[t->i_get].par);
            int idx = t->i_get;
            if (t->i_put == -1) {
                t->i_put = t->i_get;
            }
            if (++t->i_get == t->qlen) {
                t->i_get = 0;
            }
            //ets_intr_unlock();
            uint32_t old_sw_wdt = *sw_wdt;
            t->task(&t->queue[idx]);
            if (ets_loop_dont_feed_sw_wdt) {
                // Restore previous SW WDT counter, in case task fed/cleared it
                *sw_wdt = old_sw_wdt;
            }
            //ets_intr_lock();
            //printf("Done calling task %d\n", t - emu_tasks + FIRST_PRIO);
        }
        ets_intr_unlock();
    }

    if (!progress && idle_cb) {
        idle_cb(idle_arg);
    }

    return progress;
}