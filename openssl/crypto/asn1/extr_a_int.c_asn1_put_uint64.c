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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static size_t asn1_put_uint64(unsigned char b[sizeof(uint64_t)], uint64_t r)
{
    size_t off = sizeof(uint64_t);

    do {
        b[--off] = (unsigned char)r;
    } while (r >>= 8);

    return off;
}