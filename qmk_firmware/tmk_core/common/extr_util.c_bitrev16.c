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
typedef  int uint16_t ;

/* Variables and functions */
 int bitrev (int) ; 

uint16_t bitrev16(uint16_t bits) {
    bits = bitrev(bits & 0x00ff) << 8 | bitrev((bits & 0xff00) >> 8);
    return bits;
}