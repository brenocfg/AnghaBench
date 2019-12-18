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
typedef  scalar_t__ mp_obj_t ;
typedef  int /*<<< orphan*/  mp_obj_iter_buf_t ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 scalar_t__ MP_OBJ_STOP_ITERATION ; 
 scalar_t__ mp_getiter (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_iternext (scalar_t__) ; 
 int /*<<< orphan*/  mp_obj_get_array (scalar_t__,size_t*,scalar_t__**) ; 
 scalar_t__ mp_obj_is_type (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_type_ValueError ; 
 int /*<<< orphan*/  mp_type_list ; 
 int /*<<< orphan*/  mp_type_tuple ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

void mp_unpack_sequence(mp_obj_t seq_in, size_t num, mp_obj_t *items) {
    size_t seq_len;
    if (mp_obj_is_type(seq_in, &mp_type_tuple) || mp_obj_is_type(seq_in, &mp_type_list)) {
        mp_obj_t *seq_items;
        mp_obj_get_array(seq_in, &seq_len, &seq_items);
        if (seq_len < num) {
            goto too_short;
        } else if (seq_len > num) {
            goto too_long;
        }
        for (size_t i = 0; i < num; i++) {
            items[i] = seq_items[num - 1 - i];
        }
    } else {
        mp_obj_iter_buf_t iter_buf;
        mp_obj_t iterable = mp_getiter(seq_in, &iter_buf);

        for (seq_len = 0; seq_len < num; seq_len++) {
            mp_obj_t el = mp_iternext(iterable);
            if (el == MP_OBJ_STOP_ITERATION) {
                goto too_short;
            }
            items[num - 1 - seq_len] = el;
        }
        if (mp_iternext(iterable) != MP_OBJ_STOP_ITERATION) {
            goto too_long;
        }
    }
    return;

too_short:
    if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
        mp_raise_ValueError("wrong number of values to unpack");
    } else {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError,
            "need more than %d values to unpack", (int)seq_len));
    }
too_long:
    if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
        mp_raise_ValueError("wrong number of values to unpack");
    } else {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError,
            "too many values to unpack (expected %d)", (int)num));
    }
}