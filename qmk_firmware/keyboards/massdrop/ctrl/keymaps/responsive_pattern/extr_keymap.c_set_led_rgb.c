#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* r; int* g; int* b; } ;
struct TYPE_5__ {TYPE_1__ rgb; } ;
typedef  TYPE_2__ issi3733_led_t ;

/* Variables and functions */
 TYPE_2__* led_map ; 

void set_led_rgb(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b){
    issi3733_led_t *target_led = (led_map + led_id);
    *target_led->rgb.r = r;
    *target_led->rgb.g = g;
    *target_led->rgb.b = b;
}