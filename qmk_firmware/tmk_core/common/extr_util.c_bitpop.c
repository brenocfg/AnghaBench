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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

uint8_t bitpop(uint8_t bits) {
    uint8_t c;
    for (c = 0; bits; c++) bits &= bits - 1;
    return c;
    /*
        const uint8_t bit_count[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };
        return bit_count[bits>>4] + bit_count[bits&0x0F]
    */
}