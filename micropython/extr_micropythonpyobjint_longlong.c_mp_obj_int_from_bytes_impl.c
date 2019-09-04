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
typedef  int mp_longint_impl_t ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_new_int_from_ll (int) ; 

mp_obj_t mp_obj_int_from_bytes_impl(bool big_endian, size_t len, const byte *buf) {
    int delta = 1;
    if (!big_endian) {
        buf += len - 1;
        delta = -1;
    }

    mp_longint_impl_t value = 0;
    for (; len--; buf += delta) {
        value = (value << 8) | *buf;
    }
    return mp_obj_new_int_from_ll(value);
}