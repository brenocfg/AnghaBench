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
struct TYPE_3__ {scalar_t__ make_new; } ;
typedef  TYPE_1__ mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_exception_make_new ; 
 int mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_BaseException ; 
 int /*<<< orphan*/  mp_type_type ; 

bool mp_obj_is_exception_type(mp_obj_t self_in) {
    if (mp_obj_is_type(self_in, &mp_type_type)) {
        // optimisation when self_in is a builtin exception
        mp_obj_type_t *self = MP_OBJ_TO_PTR(self_in);
        if (self->make_new == mp_obj_exception_make_new) {
            return true;
        }
    }
    return mp_obj_is_subclass_fast(self_in, MP_OBJ_FROM_PTR(&mp_type_BaseException));
}