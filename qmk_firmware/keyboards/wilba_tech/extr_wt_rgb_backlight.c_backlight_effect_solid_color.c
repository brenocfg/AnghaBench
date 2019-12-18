#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  s; int /*<<< orphan*/  h; } ;
struct TYPE_10__ {int /*<<< orphan*/  brightness; TYPE_1__ color_1; } ;
struct TYPE_9__ {int /*<<< orphan*/  v; int /*<<< orphan*/  s; int /*<<< orphan*/  h; } ;
struct TYPE_8__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_2__ RGB ;
typedef  TYPE_3__ HSV ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_set_color_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ g_config ; 
 TYPE_2__ hsv_to_rgb (TYPE_3__) ; 

void backlight_effect_solid_color(void)
{
    HSV hsv = { .h = g_config.color_1.h, .s = g_config.color_1.s, .v = g_config.brightness };
    RGB rgb = hsv_to_rgb( hsv );
    backlight_set_color_all( rgb.r, rgb.g, rgb.b );
}