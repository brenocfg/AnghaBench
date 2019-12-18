#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 int /*<<< orphan*/  mp_obj_get_type_str (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_list_get (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_tuple_get (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 
 int /*<<< orphan*/  mp_type_TypeError ; 
 int /*<<< orphan*/  mp_type_list ; 
 int /*<<< orphan*/  mp_type_tuple ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

void mp_obj_get_array(mp_obj_t o, size_t *len, mp_obj_t **items) {
    if (mp_obj_is_type(o, &mp_type_tuple)) {
        mp_obj_tuple_get(o, len, items);
    } else if (mp_obj_is_type(o, &mp_type_list)) {
        mp_obj_list_get(o, len, items);
    } else {
        if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
            mp_raise_TypeError("expected tuple/list");
        } else {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
                "object '%s' isn't a tuple or list", mp_obj_get_type_str(o)));
        }
    }
}