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
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_config_save () ; 
 int /*<<< orphan*/  decrement (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ g_config ; 

void backlight_brightness_decrease(void)
{
    g_config.brightness = decrement( g_config.brightness, 8, 0, 255 );
    backlight_config_save();
}