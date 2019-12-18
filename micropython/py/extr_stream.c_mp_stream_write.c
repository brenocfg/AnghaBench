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
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  MP_OBJ_NEW_SMALL_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_const_none ; 
 scalar_t__ mp_is_nonblocking_error (int) ; 
 int /*<<< orphan*/  mp_raise_OSError (int) ; 
 int /*<<< orphan*/  mp_stream_rw (int /*<<< orphan*/ ,void*,size_t,int*,int /*<<< orphan*/ ) ; 

mp_obj_t mp_stream_write(mp_obj_t self_in, const void *buf, size_t len, byte flags) {
    int error;
    mp_uint_t out_sz = mp_stream_rw(self_in, (void*)buf, len, &error, flags);
    if (error != 0) {
        if (mp_is_nonblocking_error(error)) {
            // http://docs.python.org/3/library/io.html#io.RawIOBase.write
            // "None is returned if the raw stream is set not to block and
            // no single byte could be readily written to it."
            return mp_const_none;
        }
        mp_raise_OSError(error);
    } else {
        return MP_OBJ_NEW_SMALL_INT(out_sz);
    }
}