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
typedef  int uint ;
typedef  int mp_uint_t ;
typedef  int byte ;

/* Variables and functions */

long long mp_binary_get_int(mp_uint_t size, bool is_signed, bool big_endian, const byte *src) {
    int delta;
    if (!big_endian) {
        delta = -1;
        src += size - 1;
    } else {
        delta = 1;
    }

    long long val = 0;
    if (is_signed && *src & 0x80) {
        val = -1;
    }
    for (uint i = 0; i < size; i++) {
        val <<= 8;
        val |= *src;
        src += delta;
    }

    return val;
}