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
typedef  scalar_t__ qstr ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ MICROPY_ERROR_REPORTING ; 
 scalar_t__ MICROPY_ERROR_REPORTING_TERSE ; 
 scalar_t__ const MP_QSTR_bytes ; 
 scalar_t__ const MP_QSTR_str ; 
 TYPE_1__* mp_obj_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_exception_msg_varg (int /*<<< orphan*/ *,char*,scalar_t__ const,scalar_t__ const) ; 
 int /*<<< orphan*/  mp_raise_TypeError (char*) ; 
 int /*<<< orphan*/  mp_type_TypeError ; 
 int /*<<< orphan*/  nlr_raise (int /*<<< orphan*/ ) ; 

void bad_implicit_conversion(mp_obj_t self_in) {
    if (MICROPY_ERROR_REPORTING == MICROPY_ERROR_REPORTING_TERSE) {
        mp_raise_TypeError("can't convert to str implicitly");
    } else {
        const qstr src_name = mp_obj_get_type(self_in)->name;
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_TypeError,
            "can't convert '%q' object to %q implicitly",
            src_name, src_name == MP_QSTR_str ? MP_QSTR_bytes : MP_QSTR_str));
    }
}