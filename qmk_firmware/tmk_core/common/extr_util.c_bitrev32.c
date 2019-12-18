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
typedef  int uint32_t ;

/* Variables and functions */
 int bitrev16 (int) ; 

uint32_t bitrev32(uint32_t bits) {
    bits = (uint32_t)bitrev16(bits & 0x0000ffff) << 16 | bitrev16((bits & 0xffff0000) >> 16);
    return bits;
}