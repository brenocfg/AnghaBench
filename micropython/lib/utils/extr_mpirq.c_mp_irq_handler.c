#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ret_val; } ;
typedef  TYPE_2__ nlr_buf_t ;
struct TYPE_8__ {scalar_t__ handler; int /*<<< orphan*/  parent; TYPE_1__* methods; scalar_t__ ishard; } ;
typedef  TYPE_3__ mp_irq_obj_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* trigger ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_lock () ; 
 int /*<<< orphan*/  gc_unlock () ; 
 int /*<<< orphan*/  mp_call_function_1 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  mp_obj_print_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_plat_print ; 
 int /*<<< orphan*/  mp_sched_schedule (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mp_irq_handler(mp_irq_obj_t *self) {
    if (self->handler != mp_const_none) {
        if (self->ishard) {
            // When executing code within a handler we must lock the GC to prevent
            // any memory allocations.
            gc_lock();
            nlr_buf_t nlr;
            if (nlr_push(&nlr) == 0) {
                mp_call_function_1(self->handler, self->parent);
                nlr_pop();
            } else {
                // Uncaught exception; disable the callback so that it doesn't run again
                self->methods->trigger(self->parent, 0);
                self->handler = mp_const_none;
                printf("Uncaught exception in IRQ callback handler\n");
                mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(nlr.ret_val));
            }
            gc_unlock();
        } else {
            // Schedule call to user function
            mp_sched_schedule(self->handler, self->parent);
        }
    }
}