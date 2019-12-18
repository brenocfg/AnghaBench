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
typedef  int /*<<< orphan*/  qstr ;
struct TYPE_3__ {int /*<<< orphan*/  (* attr ) (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OP_printf (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_SENTINEL ; 
 TYPE_1__* mp_obj_get_type (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_get_type_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_AttributeError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qstr_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

void mp_store_attr(mp_obj_t base, qstr attr, mp_obj_t value) {
    DEBUG_OP_printf("store attr %p.%s <- %p\n", base, qstr_str(attr), value);
    mp_obj_type_t *type = mp_obj_get_type(base);
    if (type->attr != NULL) {
        mp_obj_t dest[2] = {MP_OBJ_SENTINEL, value};
        type->attr(base, attr, dest);
        if (dest[0] == MP_OBJ_NULL) {
            // success
            return;
        }
    }
    if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
        mp_raise_msg(&mp_type_AttributeError, "no such attribute");
    } else {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_AttributeError,
            "'%s' object has no attribute '%q'",
            mp_obj_get_type_str(base), attr));
    }
}