#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ vstr_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ mp_buffer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_BUFFER_WRITE ; 
 int /*<<< orphan*/  MP_OBJ_NULL ; 
 int /*<<< orphan*/  mp_get_buffer_raise (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_get_int (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_obj_is_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vstr_init_len (TYPE_1__*,int /*<<< orphan*/ ) ; 

mp_obj_t pyb_buf_get_for_recv(mp_obj_t o, vstr_t *vstr) {
    if (mp_obj_is_int(o)) {
        // allocate a new bytearray of given length
        vstr_init_len(vstr, mp_obj_get_int(o));
        return MP_OBJ_NULL;
    } else {
        // get the existing buffer
        mp_buffer_info_t bufinfo;
        mp_get_buffer_raise(o, &bufinfo, MP_BUFFER_WRITE);
        vstr->buf = bufinfo.buf;
        vstr->len = bufinfo.len;
        return o;
    }
}