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
 int /*<<< orphan*/  mp_obj_get_array (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_type_ValueError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

void mp_obj_get_array_fixed_n(mp_obj_t o, size_t len, mp_obj_t **items) {
    size_t seq_len;
    mp_obj_get_array(o, &seq_len, items);
    if (seq_len != len) {
        if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
            mp_raise_ValueError("tuple/list has wrong length");
        } else {
            nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError,
                "requested length %d but object has length %d", (int)len, (int)seq_len));
        }
    }
}