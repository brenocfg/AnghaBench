#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  ret_val; } ;
typedef  TYPE_1__ nlr_buf_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 int EXTI_NUM_VECTORS ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HAL_GPIO_EXTI_CLEAR_FLAG (int) ; 
 scalar_t__ __HAL_GPIO_EXTI_GET_FLAG (int) ; 
 int /*<<< orphan*/  extint_disable (int) ; 
 int /*<<< orphan*/  gc_lock () ; 
 int /*<<< orphan*/  gc_unlock () ; 
 int /*<<< orphan*/  mp_call_function_1 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  mp_obj_print_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_plat_print ; 
 int /*<<< orphan*/  mp_sched_lock () ; 
 int /*<<< orphan*/  mp_sched_schedule (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_sched_unlock () ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  pyb_extint_callback ; 
 int /*<<< orphan*/ * pyb_extint_callback_arg ; 
 int /*<<< orphan*/ * pyb_extint_hard_irq ; 

void Handle_EXTI_Irq(uint32_t line) {
    if (__HAL_GPIO_EXTI_GET_FLAG(1 << line)) {
        __HAL_GPIO_EXTI_CLEAR_FLAG(1 << line);
        if (line < EXTI_NUM_VECTORS) {
            mp_obj_t *cb = &MP_STATE_PORT(pyb_extint_callback)[line];
            if (*cb != mp_const_none) {
                // If it's a soft IRQ handler then just schedule callback for later
                if (!pyb_extint_hard_irq[line]) {
                    mp_sched_schedule(*cb, pyb_extint_callback_arg[line]);
                    return;
                }

                mp_sched_lock();
                // When executing code within a handler we must lock the GC to prevent
                // any memory allocations.  We must also catch any exceptions.
                gc_lock();
                nlr_buf_t nlr;
                if (nlr_push(&nlr) == 0) {
                    mp_call_function_1(*cb, pyb_extint_callback_arg[line]);
                    nlr_pop();
                } else {
                    // Uncaught exception; disable the callback so it doesn't run again.
                    *cb = mp_const_none;
                    extint_disable(line);
                    printf("Uncaught exception in ExtInt interrupt handler line %u\n", (unsigned int)line);
                    mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(nlr.ret_val));
                }
                gc_unlock();
                mp_sched_unlock();
            }
        }
    }
}