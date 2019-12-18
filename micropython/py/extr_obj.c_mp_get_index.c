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
typedef  size_t mp_uint_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  size_t mp_int_t ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 size_t MP_OBJ_SMALL_INT_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_get_int_maybe (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mp_obj_get_type_str (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_small_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 
 int /*<<< orphan*/  mp_raise_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_IndexError ; 
 int /*<<< orphan*/  mp_type_TypeError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

size_t mp_get_index(const mp_obj_type_t *type, size_t len, mp_obj_t index, bool is_slice) {
    mp_int_t i;
    if (mp_obj_is_small_int(index)) {
        i = MP_OBJ_SMALL_INT_VALUE(index);
    } else if (!mp_obj_get_int_maybe(index, &i)) {
        if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
            mp_raise_TypeError("indices must be integers");
        } else {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
                "%q indices must be integers, not %s",
                type->name, mp_obj_get_type_str(index)));
        }
    }

    if (i < 0) {
        i += len;
    }
    if (is_slice) {
        if (i < 0) {
            i = 0;
        } else if ((mp_uint_t)i > len) {
            i = len;
        }
    } else {
        if (i < 0 || (mp_uint_t)i >= len) {
            if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
                mp_raise_msg(&mp_type_IndexError, "index out of range");
            } else {
                nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_IndexError,
                    "%q index out of range", type->name));
            }
        }
    }

    // By this point 0 <= i <= len and so fits in a size_t
    return (size_t)i;
}