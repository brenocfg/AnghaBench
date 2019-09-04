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
struct TYPE_3__ {scalar_t__ (* subscr ) (scalar_t__,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_SENTINEL ; 
 TYPE_1__* mp_obj_get_type (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_get_type_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 
 int /*<<< orphan*/  mp_type_TypeError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__,scalar_t__) ; 

mp_obj_t mp_obj_subscr(mp_obj_t base, mp_obj_t index, mp_obj_t value) {
    mp_obj_type_t *type = mp_obj_get_type(base);
    if (type->subscr != NULL) {
        mp_obj_t ret = type->subscr(base, index, value);
        if (ret != MP_OBJ_NULL) {
            return ret;
        }
        // TODO: call base classes here?
    }
    if (value == MP_OBJ_NULL) {
        if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
            mp_raise_TypeError("object doesn't support item deletion");
        } else {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
                "'%s' object doesn't support item deletion", mp_obj_get_type_str(base)));
        }
    } else if (value == MP_OBJ_SENTINEL) {
        if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
            mp_raise_TypeError("object isn't subscriptable");
        } else {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
                "'%s' object isn't subscriptable", mp_obj_get_type_str(base)));
        }
    } else {
        if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
            mp_raise_TypeError("object doesn't support item assignment");
        } else {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
                "'%s' object doesn't support item assignment", mp_obj_get_type_str(base)));
        }
    }
}