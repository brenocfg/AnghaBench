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
typedef  scalar_t__ mp_obj_t ;
struct TYPE_2__ {size_t len; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ mp_obj_str_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_QSTR_VALUE (scalar_t__) ; 
 scalar_t__ mp_obj_is_qstr (scalar_t__) ; 
 int /*<<< orphan*/  const* qstr_data (int /*<<< orphan*/ ,size_t*) ; 

const byte *mp_obj_str_get_data_no_check(mp_obj_t self_in, size_t *len) {
    if (mp_obj_is_qstr(self_in)) {
        return qstr_data(MP_OBJ_QSTR_VALUE(self_in), len);
    } else {
        *len = ((mp_obj_str_t*)self_in)->len;
        return ((mp_obj_str_t*)self_in)->data;
    }
}