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
typedef  int /*<<< orphan*/  mp_obj_type_t ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ mp_obj_base_t ;
typedef  int /*<<< orphan*/  mp_const_obj_t ;

/* Variables and functions */
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_float (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_qstr (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_small_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_type_float ; 
 int /*<<< orphan*/  mp_type_int ; 
 int /*<<< orphan*/  mp_type_str ; 

mp_obj_type_t *mp_obj_get_type(mp_const_obj_t o_in) {
    if (mp_obj_is_small_int(o_in)) {
        return (mp_obj_type_t*)&mp_type_int;
    } else if (mp_obj_is_qstr(o_in)) {
        return (mp_obj_type_t*)&mp_type_str;
    #if MICROPY_PY_BUILTINS_FLOAT
    } else if (mp_obj_is_float(o_in)) {
        return (mp_obj_type_t*)&mp_type_float;
    #endif
    } else {
        const mp_obj_base_t *o = MP_OBJ_TO_PTR(o_in);
        return (mp_obj_type_t*)o->type;
    }
}