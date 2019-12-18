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
typedef  int uint8_t ;

/* Variables and functions */

uint8_t bitrev(uint8_t bits) {
    bits = (bits & 0x0f) << 4 | (bits & 0xf0) >> 4;
    bits = (bits & 0b00110011) << 2 | (bits & 0b11001100) >> 2;
    bits = (bits & 0b01010101) << 1 | (bits & 0b10101010) >> 1;
    return bits;
}