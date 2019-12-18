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
typedef  void* uint8_t ;

/* Variables and functions */
 void* clipping_num_leds ; 
 void* clipping_start_pos ; 

void rgblight_set_clipping_range(uint8_t start_pos, uint8_t num_leds) {
    clipping_start_pos = start_pos;
    clipping_num_leds  = num_leds;
}