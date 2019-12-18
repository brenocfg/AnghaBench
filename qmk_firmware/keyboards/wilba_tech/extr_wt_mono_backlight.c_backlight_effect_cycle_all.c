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
typedef  int uint8_t ;
struct TYPE_2__ {int effect_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_set_brightness_all (int) ; 
 TYPE_1__ g_config ; 
 int g_tick ; 

void backlight_effect_cycle_all(void)
{
	uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;

	backlight_set_brightness_all( offset );
}