#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
struct TYPE_4__ {TYPE_1__ color_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_config_save () ; 
 TYPE_2__ g_config ; 
 int /*<<< orphan*/  increment (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void backlight_color_1_sat_increase(void)
{
    g_config.color_1.s = increment( g_config.color_1.s, 8, 0, 255 );
    backlight_config_save();
}