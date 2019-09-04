#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ mp_obj_dict_t ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MAP_LOOKUP_ADD_IF_NOT_FOUND ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_check_self (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_ensure_not_fixed (TYPE_1__*) ; 
 TYPE_2__* mp_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_is_dict_type (int /*<<< orphan*/ ) ; 

mp_obj_t mp_obj_dict_store(mp_obj_t self_in, mp_obj_t key, mp_obj_t value) {
    mp_check_self(mp_obj_is_dict_type(self_in));
    mp_obj_dict_t *self = MP_OBJ_TO_PTR(self_in);
    mp_ensure_not_fixed(self);
    mp_map_lookup(&self->map, key, MP_MAP_LOOKUP_ADD_IF_NOT_FOUND)->value = value;
    return self_in;
}