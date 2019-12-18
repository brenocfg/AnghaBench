#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_2__ {void* b; void* g; void* r; } ;

/* Variables and functions */
 int ISSI3733_LED_COUNT ; 
 TYPE_1__* led_buffer ; 
 int /*<<< orphan*/  led_matrix_massdrop_config_override (int) ; 

void led_set_one(int i, uint8_t r, uint8_t g, uint8_t b) {
    if (i < ISSI3733_LED_COUNT) {
#ifdef USE_MASSDROP_CONFIGURATOR
        led_matrix_massdrop_config_override(i);
#else
        led_buffer[i].r = r;
        led_buffer[i].g = g;
        led_buffer[i].b = b;
#endif
    }
}