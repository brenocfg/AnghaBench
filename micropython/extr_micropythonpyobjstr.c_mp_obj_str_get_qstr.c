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
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
typedef  TYPE_1__ mp_obj_str_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_QSTR_VALUE (int /*<<< orphan*/ ) ; 
 TYPE_1__* MP_OBJ_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_implicit_conversion (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_qstr (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_type_str ; 
 int /*<<< orphan*/  qstr_from_strn (char*,int /*<<< orphan*/ ) ; 

qstr mp_obj_str_get_qstr(mp_obj_t self_in) {
    if (mp_obj_is_qstr(self_in)) {
        return MP_OBJ_QSTR_VALUE(self_in);
    } else if (mp_obj_is_type(self_in, &mp_type_str)) {
        mp_obj_str_t *self = MP_OBJ_TO_PTR(self_in);
        return qstr_from_strn((char*)self->data, self->len);
    } else {
        bad_implicit_conversion(self_in);
    }
}