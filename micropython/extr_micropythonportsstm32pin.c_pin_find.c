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
typedef  scalar_t__ mp_obj_t ;
typedef  int /*<<< orphan*/  mp_map_t ;
struct TYPE_3__ {scalar_t__ value; } ;
typedef  TYPE_1__ mp_map_elem_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MAP_LOOKUP ; 
 scalar_t__ MP_OBJ_FROM_PTR (int /*<<< orphan*/  const*) ; 
 scalar_t__ MP_OBJ_NULL ; 
 int /*<<< orphan*/  const* MP_OBJ_TO_PTR (scalar_t__) ; 
 scalar_t__ MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_REPR ; 
 int /*<<< orphan*/  PRINT_STR ; 
 scalar_t__ mp_call_function_1 (scalar_t__,scalar_t__) ; 
 scalar_t__ mp_const_none ; 
 TYPE_1__* mp_map_lookup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_obj_dict_get_map (scalar_t__) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_print (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_str_get_str (scalar_t__) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_type_ValueError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pin_board_pins_locals_dict ; 
 scalar_t__ pin_class_debug ; 
 int /*<<< orphan*/  pin_class_map_dict ; 
 int /*<<< orphan*/  pin_class_mapper ; 
 int /*<<< orphan*/  pin_cpu_pins_locals_dict ; 
 int /*<<< orphan*/ * pin_find_named_pin (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pin_type ; 
 int /*<<< orphan*/  printf (char*) ; 

const pin_obj_t *pin_find(mp_obj_t user_obj) {
    const pin_obj_t *pin_obj;

    // If a pin was provided, then use it
    if (mp_obj_is_type(user_obj, &pin_type)) {
        pin_obj = MP_OBJ_TO_PTR(user_obj);
        if (pin_class_debug) {
            printf("Pin map passed pin ");
            mp_obj_print(MP_OBJ_FROM_PTR(pin_obj), PRINT_STR);
            printf("\n");
        }
        return pin_obj;
    }

    if (MP_STATE_PORT(pin_class_mapper) != mp_const_none) {
        mp_obj_t o = mp_call_function_1(MP_STATE_PORT(pin_class_mapper), user_obj);
        if (o != mp_const_none) {
            if (!mp_obj_is_type(o, &pin_type)) {
                mp_raise_ValueError("Pin.mapper didn't return a Pin object");
            }
            if (pin_class_debug) {
                printf("Pin.mapper maps ");
                mp_obj_print(user_obj, PRINT_REPR);
                printf(" to ");
                mp_obj_print(o, PRINT_STR);
                printf("\n");
            }
            return MP_OBJ_TO_PTR(o);
        }
        // The pin mapping function returned mp_const_none, fall through to
        // other lookup methods.
    }

    if (MP_STATE_PORT(pin_class_map_dict) != mp_const_none) {
        mp_map_t *pin_map_map = mp_obj_dict_get_map(MP_STATE_PORT(pin_class_map_dict));
        mp_map_elem_t *elem = mp_map_lookup(pin_map_map, user_obj, MP_MAP_LOOKUP);
        if (elem != NULL && elem->value != MP_OBJ_NULL) {
            mp_obj_t o = elem->value;
            if (pin_class_debug) {
                printf("Pin.map_dict maps ");
                mp_obj_print(user_obj, PRINT_REPR);
                printf(" to ");
                mp_obj_print(o, PRINT_STR);
                printf("\n");
            }
            return MP_OBJ_TO_PTR(o);
        }
    }

    // See if the pin name matches a board pin
    pin_obj = pin_find_named_pin(&pin_board_pins_locals_dict, user_obj);
    if (pin_obj) {
        if (pin_class_debug) {
            printf("Pin.board maps ");
            mp_obj_print(user_obj, PRINT_REPR);
            printf(" to ");
            mp_obj_print(MP_OBJ_FROM_PTR(pin_obj), PRINT_STR);
            printf("\n");
        }
        return pin_obj;
    }

    // See if the pin name matches a cpu pin
    pin_obj = pin_find_named_pin(&pin_cpu_pins_locals_dict, user_obj);
    if (pin_obj) {
        if (pin_class_debug) {
            printf("Pin.cpu maps ");
            mp_obj_print(user_obj, PRINT_REPR);
            printf(" to ");
            mp_obj_print(MP_OBJ_FROM_PTR(pin_obj), PRINT_STR);
            printf("\n");
        }
        return pin_obj;
    }

    nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "Pin(%s) doesn't exist", mp_obj_str_get_str(user_obj)));
}