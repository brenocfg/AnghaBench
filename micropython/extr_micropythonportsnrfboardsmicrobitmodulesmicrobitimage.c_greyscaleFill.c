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
typedef  int mp_int_t ;
struct TYPE_3__ {int width; int height; int* byte_data; } ;
typedef  TYPE_1__ greyscale_t ;

/* Variables and functions */

void greyscaleFill(greyscale_t * p_greyscale, mp_int_t val) {
    mp_int_t byte = (val<<4) | val;
    for (int i = 0; i < ((p_greyscale->width*p_greyscale->height+1)>>1); i++) {
        p_greyscale->byte_data[i] = byte;
    }
}