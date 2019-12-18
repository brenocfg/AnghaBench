#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_type_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_2__ {int /*<<< orphan*/ * subobj; } ;
typedef  TYPE_1__ mp_obj_instance_t ;
typedef  int /*<<< orphan*/  mp_const_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_FROM_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 scalar_t__ MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_obj_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_is_subclass_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mp_obj_t mp_instance_cast_to_native_base(mp_const_obj_t self_in, mp_const_obj_t native_type) {
    mp_obj_type_t *self_type = mp_obj_get_type(self_in);
    if (!mp_obj_is_subclass_fast(MP_OBJ_FROM_PTR(self_type), native_type)) {
        return MP_OBJ_NULL;
    }
    mp_obj_instance_t *self = (mp_obj_instance_t*)MP_OBJ_TO_PTR(self_in);
    return self->subobj[0];
}