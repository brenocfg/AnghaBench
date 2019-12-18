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
struct TYPE_3__ {scalar_t__ (* binary_op ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  BytesWarning ; 
 int /*<<< orphan*/  MP_BINARY_OP_EQUAL ; 
 scalar_t__ MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_WARN_CAT (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_const_none ; 
 scalar_t__ mp_const_true ; 
 TYPE_1__* mp_obj_get_type (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_is_float (scalar_t__) ; 
 scalar_t__ mp_obj_is_small_int (scalar_t__) ; 
 scalar_t__ mp_obj_is_str (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 int mp_obj_str_equal (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mp_type_bytes ; 
 int /*<<< orphan*/  mp_type_complex ; 
 int /*<<< orphan*/  mp_warning (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

bool mp_obj_equal(mp_obj_t o1, mp_obj_t o2) {
    // Float (and complex) NaN is never equal to anything, not even itself,
    // so we must have a special check here to cover those cases.
    if (o1 == o2
        #if MICROPY_PY_BUILTINS_FLOAT
        && !mp_obj_is_float(o1)
        #endif
        #if MICROPY_PY_BUILTINS_COMPLEX
        && !mp_obj_is_type(o1, &mp_type_complex)
        #endif
        ) {
        return true;
    }
    if (o1 == mp_const_none || o2 == mp_const_none) {
        return false;
    }

    // fast path for small ints
    if (mp_obj_is_small_int(o1)) {
        if (mp_obj_is_small_int(o2)) {
            // both SMALL_INT, and not equal if we get here
            return false;
        } else {
            mp_obj_t temp = o2; o2 = o1; o1 = temp;
            // o2 is now the SMALL_INT, o1 is not
            // fall through to generic op
        }
    }

    // fast path for strings
    if (mp_obj_is_str(o1)) {
        if (mp_obj_is_str(o2)) {
            // both strings, use special function
            return mp_obj_str_equal(o1, o2);
        } else {
            // a string is never equal to anything else
            goto str_cmp_err;
        }
    } else if (mp_obj_is_str(o2)) {
        // o1 is not a string (else caught above), so the objects are not equal
    str_cmp_err:
        #if MICROPY_PY_STR_BYTES_CMP_WARN
        if (mp_obj_is_type(o1, &mp_type_bytes) || mp_obj_is_type(o2, &mp_type_bytes)) {
            mp_warning(MP_WARN_CAT(BytesWarning), "Comparison between bytes and str");
        }
        #endif
        return false;
    }

    // generic type, call binary_op(MP_BINARY_OP_EQUAL)
    mp_obj_type_t *type = mp_obj_get_type(o1);
    if (type->binary_op != NULL) {
        mp_obj_t r = type->binary_op(MP_BINARY_OP_EQUAL, o1, o2);
        if (r != MP_OBJ_NULL) {
            return r == mp_const_true ? true : false;
        }
    }

    // equality not implemented, and objects are not the same object, so
    // they are defined as not equal
    return false;
}