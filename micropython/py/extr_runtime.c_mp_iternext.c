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
struct TYPE_6__ {scalar_t__ ret_val; } ;
typedef  TYPE_1__ nlr_buf_t ;
struct TYPE_7__ {scalar_t__ (* iternext ) (scalar_t__) ;} ;
typedef  TYPE_2__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;
struct TYPE_8__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_3__ mp_obj_base_t ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_STOP_ITERATION ; 
 int /*<<< orphan*/  MP_QSTR___next__ ; 
 int /*<<< orphan*/  MP_STACK_CHECK () ; 
 scalar_t__ mp_call_method_n_kw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mp_load_method_maybe (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_2__* mp_obj_get_type (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_get_type_str (scalar_t__) ; 
 scalar_t__ mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 
 int /*<<< orphan*/  mp_type_StopIteration ; 
 int /*<<< orphan*/  mp_type_TypeError ; 
 int /*<<< orphan*/  nlr_jump (scalar_t__) ; 
 int /*<<< orphan*/  nlr_pop () ; 
 scalar_t__ nlr_push (TYPE_1__*) ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__) ; 

mp_obj_t mp_iternext(mp_obj_t o_in) {
    MP_STACK_CHECK(); // enumerate, filter, map and zip can recursively call mp_iternext
    mp_obj_type_t *type = mp_obj_get_type(o_in);
    if (type->iternext != NULL) {
        return type->iternext(o_in);
    } else {
        // check for __next__ method
        mp_obj_t dest[2];
        mp_load_method_maybe(o_in, MP_QSTR___next__, dest);
        if (dest[0] != MP_OBJ_NULL) {
            // __next__ exists, call it and return its result
            nlr_buf_t nlr;
            if (nlr_push(&nlr) == 0) {
                mp_obj_t ret = mp_call_method_n_kw(0, 0, dest);
                nlr_pop();
                return ret;
            } else {
                if (mp_obj_is_subclass_fast(MP_OBJ_FROM_PTR(((mp_obj_base_t*)nlr.ret_val)->type), MP_OBJ_FROM_PTR(&mp_type_StopIteration))) {
                    return MP_OBJ_STOP_ITERATION;
                } else {
                    nlr_jump(nlr.ret_val);
                }
            }
        } else {
            if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
                mp_raise_TypeError("object not an iterator");
            } else {
                nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
                    "'%s' object isn't an iterator", mp_obj_get_type_str(o_in)));
            }
        }
    }
}