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
typedef  scalar_t__ mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int mp_int_t ;
struct TYPE_3__ {char typecode; int /*<<< orphan*/  len; void* buf; } ;
typedef  TYPE_1__ mp_buffer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_STR_DATA_LEN (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_BUFFER_READ ; 
 scalar_t__ str_data ; 
 int /*<<< orphan*/  str_len ; 

mp_int_t mp_obj_str_get_buffer(mp_obj_t self_in, mp_buffer_info_t *bufinfo, mp_uint_t flags) {
    if (flags == MP_BUFFER_READ) {
        GET_STR_DATA_LEN(self_in, str_data, str_len);
        bufinfo->buf = (void*)str_data;
        bufinfo->len = str_len;
        bufinfo->typecode = 'B'; // bytes should be unsigned, so should unicode byte-access
        return 0;
    } else {
        // can't write to a string
        return 1;
    }
}