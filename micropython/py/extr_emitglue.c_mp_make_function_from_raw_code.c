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
struct TYPE_6__ {int kind; int scope_flags; int /*<<< orphan*/  const_table; int /*<<< orphan*/  fun_data; int /*<<< orphan*/  type_sig; int /*<<< orphan*/  n_pos_args; } ;
typedef  TYPE_1__ mp_raw_code_t ;
typedef  scalar_t__ mp_obj_t ;
struct TYPE_7__ {TYPE_1__ const* rc; } ;
typedef  TYPE_2__ mp_obj_fun_bc_t ;
struct TYPE_8__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_3__ mp_obj_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OP_printf (char*,TYPE_1__ const*) ; 
 int MP_CODE_BYTECODE ; 
#define  MP_CODE_NATIVE_ASM 130 
#define  MP_CODE_NATIVE_PY 129 
#define  MP_CODE_NATIVE_VIPER 128 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_TO_PTR (scalar_t__) ; 
 int MP_SCOPE_FLAG_GENERATOR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_obj_new_fun_asm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_new_fun_bc (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_new_fun_native (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_type_dict ; 
 int /*<<< orphan*/  mp_type_gen_wrap ; 
 int /*<<< orphan*/  mp_type_native_gen_wrap ; 
 int /*<<< orphan*/  mp_type_tuple ; 

mp_obj_t mp_make_function_from_raw_code(const mp_raw_code_t *rc, mp_obj_t def_args, mp_obj_t def_kw_args) {
    DEBUG_OP_printf("make_function_from_raw_code %p\n", rc);
    assert(rc != NULL);

    // def_args must be MP_OBJ_NULL or a tuple
    assert(def_args == MP_OBJ_NULL || mp_obj_is_type(def_args, &mp_type_tuple));

    // def_kw_args must be MP_OBJ_NULL or a dict
    assert(def_kw_args == MP_OBJ_NULL || mp_obj_is_type(def_kw_args, &mp_type_dict));

    // make the function, depending on the raw code kind
    mp_obj_t fun;
    switch (rc->kind) {
        #if MICROPY_EMIT_NATIVE
        case MP_CODE_NATIVE_PY:
        case MP_CODE_NATIVE_VIPER:
            fun = mp_obj_new_fun_native(def_args, def_kw_args, rc->fun_data, rc->const_table);
            // Check for a generator function, and if so change the type of the object
            if ((rc->scope_flags & MP_SCOPE_FLAG_GENERATOR) != 0) {
                ((mp_obj_base_t*)MP_OBJ_TO_PTR(fun))->type = &mp_type_native_gen_wrap;
            }
            break;
        #endif
        #if MICROPY_EMIT_INLINE_ASM
        case MP_CODE_NATIVE_ASM:
            fun = mp_obj_new_fun_asm(rc->n_pos_args, rc->fun_data, rc->type_sig);
            break;
        #endif
        default:
            // rc->kind should always be set and BYTECODE is the only remaining case
            assert(rc->kind == MP_CODE_BYTECODE);
            fun = mp_obj_new_fun_bc(def_args, def_kw_args, rc->fun_data, rc->const_table);
            // check for generator functions and if so change the type of the object
            if ((rc->scope_flags & MP_SCOPE_FLAG_GENERATOR) != 0) {
                ((mp_obj_base_t*)MP_OBJ_TO_PTR(fun))->type = &mp_type_gen_wrap;
            }

            #if MICROPY_PY_SYS_SETTRACE
            mp_obj_fun_bc_t *self_fun = (mp_obj_fun_bc_t *)MP_OBJ_TO_PTR(fun);
            self_fun->rc = rc;
            #endif

            break;
    }

    return fun;
}