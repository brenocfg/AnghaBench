#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_vm_return_kind_t ;
struct TYPE_7__ {scalar_t__ (* iternext ) (scalar_t__) ;} ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (TYPE_1__*) ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_STOP_ITERATION ; 
 int /*<<< orphan*/  MP_QSTR___next__ ; 
 int /*<<< orphan*/  MP_QSTR_close ; 
 int /*<<< orphan*/  MP_QSTR_send ; 
 int /*<<< orphan*/  MP_QSTR_throw ; 
 int /*<<< orphan*/  MP_VM_RETURN_EXCEPTION ; 
 int /*<<< orphan*/  MP_VM_RETURN_NORMAL ; 
 int /*<<< orphan*/  MP_VM_RETURN_YIELD ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_call_method_n_kw (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ mp_const_none ; 
 int /*<<< orphan*/  mp_load_method (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mp_load_method_maybe (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ mp_make_raise_obj (scalar_t__) ; 
 scalar_t__ mp_obj_exception_match (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_gen_resume (scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 TYPE_1__* mp_obj_get_type (scalar_t__) ; 
 scalar_t__ mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_new_exception_msg (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ mp_type_GeneratorExit ; 
 int /*<<< orphan*/  mp_type_RuntimeError ; 
 TYPE_1__ mp_type_StopIteration ; 
 TYPE_1__ mp_type_gen_instance ; 
 scalar_t__ stub1 (scalar_t__) ; 

mp_vm_return_kind_t mp_resume(mp_obj_t self_in, mp_obj_t send_value, mp_obj_t throw_value, mp_obj_t *ret_val) {
    assert((send_value != MP_OBJ_NULL) ^ (throw_value != MP_OBJ_NULL));
    mp_obj_type_t *type = mp_obj_get_type(self_in);

    if (type == &mp_type_gen_instance) {
        return mp_obj_gen_resume(self_in, send_value, throw_value, ret_val);
    }

    if (type->iternext != NULL && send_value == mp_const_none) {
        mp_obj_t ret = type->iternext(self_in);
        *ret_val = ret;
        if (ret != MP_OBJ_STOP_ITERATION) {
            return MP_VM_RETURN_YIELD;
        } else {
            // Emulate raise StopIteration()
            // Special case, handled in vm.c
            return MP_VM_RETURN_NORMAL;
        }
    }

    mp_obj_t dest[3]; // Reserve slot for send() arg

    // Python instance iterator protocol
    if (send_value == mp_const_none) {
        mp_load_method_maybe(self_in, MP_QSTR___next__, dest);
        if (dest[0] != MP_OBJ_NULL) {
            *ret_val = mp_call_method_n_kw(0, 0, dest);
            return MP_VM_RETURN_YIELD;
        }
    }

    // Either python instance generator protocol, or native object
    // generator protocol.
    if (send_value != MP_OBJ_NULL) {
        mp_load_method(self_in, MP_QSTR_send, dest);
        dest[2] = send_value;
        *ret_val = mp_call_method_n_kw(1, 0, dest);
        return MP_VM_RETURN_YIELD;
    }

    assert(throw_value != MP_OBJ_NULL);
    {
        if (mp_obj_is_subclass_fast(MP_OBJ_FROM_PTR(mp_obj_get_type(throw_value)), MP_OBJ_FROM_PTR(&mp_type_GeneratorExit))) {
            mp_load_method_maybe(self_in, MP_QSTR_close, dest);
            if (dest[0] != MP_OBJ_NULL) {
                // TODO: Exceptions raised in close() are not propagated,
                // printed to sys.stderr
                *ret_val = mp_call_method_n_kw(0, 0, dest);
                // We assume one can't "yield" from close()
                return MP_VM_RETURN_NORMAL;
            }
        } else {
            mp_load_method_maybe(self_in, MP_QSTR_throw, dest);
            if (dest[0] != MP_OBJ_NULL) {
                dest[2] = throw_value;
                *ret_val = mp_call_method_n_kw(1, 0, dest);
                // If .throw() method returned, we assume it's value to yield
                // - any exception would be thrown with nlr_raise().
                return MP_VM_RETURN_YIELD;
            }
        }
        // If there's nowhere to throw exception into, then we assume that object
        // is just incapable to handle it, so any exception thrown into it
        // will be propagated up. This behavior is approved by test_pep380.py
        // test_delegation_of_close_to_non_generator(),
        //  test_delegating_throw_to_non_generator()
        if (mp_obj_exception_match(throw_value, MP_OBJ_FROM_PTR(&mp_type_StopIteration))) {
            // PEP479: if StopIteration is raised inside a generator it is replaced with RuntimeError
            *ret_val = mp_obj_new_exception_msg(&mp_type_RuntimeError, "generator raised StopIteration");
        } else {
            *ret_val = mp_make_raise_obj(throw_value);
        }
        return MP_VM_RETURN_EXCEPTION;
    }
}