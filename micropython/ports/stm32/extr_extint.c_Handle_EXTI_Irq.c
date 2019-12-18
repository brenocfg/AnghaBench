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
 int /*<<< orphan*/  MICROPY_ERROR_PRINTER ; 
 scalar_t__ MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__* MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PENDSV_DISPATCH_CYW43 ; 
 int /*<<< orphan*/  __HAL_GPIO_EXTI_CLEAR_FLAG (int) ; 
 scalar_t__ __HAL_GPIO_EXTI_GET_FLAG (int) ; 
 int /*<<< orphan*/  extint_disable (int) ; 
 int /*<<< orphan*/  gc_lock () ; 
 int /*<<< orphan*/  gc_unlock () ; 
 int /*<<< orphan*/  mp_call_function_1 (scalar_t__,scalar_t__) ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  mp_obj_print_exception (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mp_plat_print ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mp_sched_lock () ; 
 int /*<<< orphan*/  mp_sched_schedule (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mp_sched_unlock () ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_1__*) ; 
 int /*<<< orphan*/  pendsv_schedule_dispatch (int /*<<< orphan*/ ,void (*) ()) ; 
 int /*<<< orphan*/  pyb_extint_callback ; 
 scalar_t__* pyb_extint_callback_arg ; 
 int /*<<< orphan*/ * pyb_extint_hard_irq ; 
 int /*<<< orphan*/  pyb_pin_WL_HOST_WAKE ; 

void Handle_EXTI_Irq(uint32_t line) {
    if (__HAL_GPIO_EXTI_GET_FLAG(1 << line)) {
        __HAL_GPIO_EXTI_CLEAR_FLAG(1 << line);
        if (line < EXTI_NUM_VECTORS) {
            mp_obj_t *cb = &MP_STATE_PORT(pyb_extint_callback)[line];
            #if MICROPY_PY_NETWORK_CYW43 && defined(pyb_pin_WL_HOST_WAKE)
            if (pyb_extint_callback_arg[line] == MP_OBJ_FROM_PTR(pyb_pin_WL_HOST_WAKE)) {
                extern void (*cyw43_poll)(void);
                if (cyw43_poll) {
                    pendsv_schedule_dispatch(PENDSV_DISPATCH_CYW43, cyw43_poll);
                }
                return;
            }
            #endif
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
                    mp_printf(MICROPY_ERROR_PRINTER, "uncaught exception in ExtInt interrupt handler line %u\n", (unsigned int)line);
                    mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(nlr.ret_val));
                }
                gc_unlock();
                mp_sched_unlock();
            }
        }
    }
}