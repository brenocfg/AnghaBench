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
typedef  int /*<<< orphan*/  pin_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_dict_t ;
typedef  int /*<<< orphan*/  mp_map_t ;
struct TYPE_3__ {int /*<<< orphan*/  const* value; } ;
typedef  TYPE_1__ mp_map_elem_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MAP_LOOKUP ; 
 TYPE_1__* mp_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_obj_dict_get_map (int /*<<< orphan*/ ) ; 

const pin_obj_t *pin_find_named_pin(const mp_obj_dict_t *named_pins, mp_obj_t name) {
    mp_map_t *named_map = mp_obj_dict_get_map((mp_obj_t)named_pins);
    mp_map_elem_t *named_elem = mp_map_lookup(named_map, name, MP_MAP_LOOKUP);
    if (named_elem != NULL && named_elem->value != NULL) {
        return named_elem->value;
    }
    return NULL;
}