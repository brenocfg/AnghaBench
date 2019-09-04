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
typedef  unsigned int uint8_t ;
typedef  unsigned int mp_int_t ;
struct TYPE_3__ {unsigned int width; unsigned int* byte_data; } ;
typedef  TYPE_1__ greyscale_t ;

/* Variables and functions */

void greyscaleSetPixelValue(greyscale_t * p_greyscale, mp_int_t x, mp_int_t y, mp_int_t val) {
    unsigned int index = y*p_greyscale->width+x;
    unsigned int shift = ((index<<2)&4);
    uint8_t mask = 240 >> shift;
    p_greyscale->byte_data[index>>1] = (p_greyscale->byte_data[index>>1] & mask) | (val << shift);
}