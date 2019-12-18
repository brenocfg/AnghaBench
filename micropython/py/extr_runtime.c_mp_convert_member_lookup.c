#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ name; } ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  scalar_t__ mp_obj_t ;
struct TYPE_14__ {scalar_t__ fun; } ;
typedef  TYPE_2__ mp_obj_static_class_method_t ;
struct TYPE_15__ {TYPE_1__* type; } ;
typedef  TYPE_3__ mp_obj_base_t ;

/* Variables and functions */
 scalar_t__ MP_OBJ_FROM_PTR (TYPE_1__ const*) ; 
 scalar_t__ MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_TO_PTR (scalar_t__) ; 
 scalar_t__ MP_QSTR_closure ; 
 scalar_t__ MP_QSTR_generator ; 
 TYPE_1__* mp_obj_get_type (scalar_t__) ; 
 scalar_t__ mp_obj_is_fun (scalar_t__) ; 
 scalar_t__ mp_obj_is_obj (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_obj_new_checked_fun (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  mp_type_classmethod ; 
 TYPE_1__ const mp_type_fun_builtin_0 ; 
 TYPE_1__ const mp_type_fun_builtin_1 ; 
 TYPE_1__ const mp_type_fun_builtin_2 ; 
 TYPE_1__ const mp_type_fun_builtin_3 ; 
 TYPE_1__ const mp_type_fun_builtin_var ; 
 int /*<<< orphan*/  mp_type_staticmethod ; 
 int /*<<< orphan*/  mp_type_type ; 

void mp_convert_member_lookup(mp_obj_t self, const mp_obj_type_t *type, mp_obj_t member, mp_obj_t *dest) {
    if (mp_obj_is_type(member, &mp_type_staticmethod)) {
        // return just the function
        dest[0] = ((mp_obj_static_class_method_t*)MP_OBJ_TO_PTR(member))->fun;
    } else if (mp_obj_is_type(member, &mp_type_classmethod)) {
        // return a bound method, with self being the type of this object
        // this type should be the type of the original instance, not the base
        // type (which is what is passed in the 'type' argument to this function)
        if (self != MP_OBJ_NULL) {
            type = mp_obj_get_type(self);
        }
        dest[0] = ((mp_obj_static_class_method_t*)MP_OBJ_TO_PTR(member))->fun;
        dest[1] = MP_OBJ_FROM_PTR(type);
    } else if (mp_obj_is_type(member, &mp_type_type)) {
        // Don't try to bind types (even though they're callable)
        dest[0] = member;
    } else if (mp_obj_is_fun(member)
        || (mp_obj_is_obj(member)
            && (((mp_obj_base_t*)MP_OBJ_TO_PTR(member))->type->name == MP_QSTR_closure
                || ((mp_obj_base_t*)MP_OBJ_TO_PTR(member))->type->name == MP_QSTR_generator))) {
        // only functions, closures and generators objects can be bound to self
        #if MICROPY_BUILTIN_METHOD_CHECK_SELF_ARG
        const mp_obj_type_t *m_type = ((mp_obj_base_t*)MP_OBJ_TO_PTR(member))->type;
        if (self == MP_OBJ_NULL
            && (m_type == &mp_type_fun_builtin_0
                || m_type == &mp_type_fun_builtin_1
                || m_type == &mp_type_fun_builtin_2
                || m_type == &mp_type_fun_builtin_3
                || m_type == &mp_type_fun_builtin_var)) {
            // we extracted a builtin method without a first argument, so we must
            // wrap this function in a type checker
            dest[0] = mp_obj_new_checked_fun(type, member);
        } else
        #endif
        {
            // return a bound method, with self being this object
            dest[0] = member;
            dest[1] = self;
        }
    } else {
        // class member is a value, so just return that value
        dest[0] = member;
    }
}