#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ret_val; } ;
typedef  TYPE_1__ nlr_buf_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_5__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_2__ mp_obj_base_t ;
typedef  int /*<<< orphan*/  MP_STATE_VM ;

/* Variables and functions */
#define  ASYNC_MODE_ANIMATION 129 
#define  ASYNC_MODE_CLEAR 128 
 int /*<<< orphan*/  BLANK_IMAGE ; 
 scalar_t__ MILLISECONDS_PER_MACRO_TICK ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_OBJ_STOP_ITERATION ; 
 int /*<<< orphan*/ ** MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_data ; 
 scalar_t__ async_delay ; 
 int /*<<< orphan*/  async_iterator ; 
 int async_mode ; 
 int /*<<< orphan*/  async_stop () ; 
 scalar_t__ async_tick ; 
 int /*<<< orphan*/  draw_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_lock () ; 
 int /*<<< orphan*/  gc_unlock () ; 
 int /*<<< orphan*/  microbit_display_obj ; 
 int /*<<< orphan*/  microbit_display_show (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_iternext_allow_raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_obj_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_plat_print ; 
 int /*<<< orphan*/  mp_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_MemoryError ; 
 int /*<<< orphan*/  mp_type_StopIteration ; 
 int /*<<< orphan*/  nlr_pop () ; 
 int /*<<< orphan*/  nlr_push (TYPE_1__*) ; 

__attribute__((used)) static void microbit_display_update(void) {
    async_tick += MILLISECONDS_PER_MACRO_TICK;
    if (async_tick < async_delay) {
        return;
    }
    async_tick = 0;
    switch (async_mode) {
        case ASYNC_MODE_ANIMATION:
        {
            if (MP_STATE_PORT(async_data)[0] == NULL || MP_STATE_PORT(async_data)[1] == NULL) {
                async_stop();
                break;
            }
            /* WARNING: We are executing in an interrupt handler.
             * If an exception is raised here then we must hand it to the VM. */
            mp_obj_t obj;
            nlr_buf_t nlr;
            gc_lock();
            if (nlr_push(&nlr) == 0) {
                obj = mp_iternext_allow_raise(async_iterator);
                nlr_pop();
                gc_unlock();
            } else {
                gc_unlock();
                if (!mp_obj_is_subclass_fast(MP_OBJ_FROM_PTR(((mp_obj_base_t*)nlr.ret_val)->type),
                    MP_OBJ_FROM_PTR(&mp_type_StopIteration))) {
                    // An exception other than StopIteration, so set it for the VM to raise later
                    // If memory error, write an appropriate message.
                    if (mp_obj_get_type(nlr.ret_val) == &mp_type_MemoryError) {
                        mp_printf(&mp_plat_print, "Allocation in interrupt handler");
                    }
                    MP_STATE_VM(mp_pending_exception) = MP_OBJ_FROM_PTR(nlr.ret_val);
                }
                obj = MP_OBJ_STOP_ITERATION;
            }
            draw_object(obj);
            break;
        }
        case ASYNC_MODE_CLEAR:
            microbit_display_show(&microbit_display_obj, BLANK_IMAGE);
            async_stop();
            break;
    }
}