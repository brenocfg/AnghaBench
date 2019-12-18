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
struct TYPE_3__ {int /*<<< orphan*/  (* unary_op ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_STR_LEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 int /*<<< orphan*/  MP_UNARY_OP_LEN ; 
 int /*<<< orphan*/  l ; 
 TYPE_1__* mp_obj_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_str (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_bytes ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mp_obj_t mp_obj_len_maybe(mp_obj_t o_in) {
    if (
#if !MICROPY_PY_BUILTINS_STR_UNICODE
        // It's simple - unicode is slow, non-unicode is fast
        mp_obj_is_str(o_in) ||
#endif
        mp_obj_is_type(o_in, &mp_type_bytes)) {
        GET_STR_LEN(o_in, l);
        return MP_OBJ_NEW_SMALL_INT(l);
    } else {
        mp_obj_type_t *type = mp_obj_get_type(o_in);
        if (type->unary_op != NULL) {
            return type->unary_op(MP_UNARY_OP_LEN, o_in);
        } else {
            return MP_OBJ_NULL;
        }
    }
}