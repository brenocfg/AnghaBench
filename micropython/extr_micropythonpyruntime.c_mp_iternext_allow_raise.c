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
struct TYPE_3__ {scalar_t__ (* iternext ) (scalar_t__) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 scalar_t__ MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_QSTR___next__ ; 
 scalar_t__ mp_call_method_n_kw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mp_load_method_maybe (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_1__* mp_obj_get_type (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_get_type_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 
 int /*<<< orphan*/  mp_type_TypeError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__) ; 

mp_obj_t mp_iternext_allow_raise(mp_obj_t o_in) {
    mp_obj_type_t *type = mp_obj_get_type(o_in);
    if (type->iternext != NULL) {
        return type->iternext(o_in);
    } else {
        // check for __next__ method
        mp_obj_t dest[2];
        mp_load_method_maybe(o_in, MP_QSTR___next__, dest);
        if (dest[0] != MP_OBJ_NULL) {
            // __next__ exists, call it and return its result
            return mp_call_method_n_kw(0, 0, dest);
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