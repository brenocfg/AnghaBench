#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {scalar_t__ use_7u_spacebar; int /*<<< orphan*/  brightness; } ;
struct TYPE_10__ {int /*<<< orphan*/  s; int /*<<< orphan*/  h; } ;
struct TYPE_9__ {int /*<<< orphan*/  v; int /*<<< orphan*/  s; int /*<<< orphan*/  h; } ;
struct TYPE_8__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ RGB ;
typedef  TYPE_2__ HSV ;
typedef  TYPE_3__ HS ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backlight_set_color_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ g_config ; 
 TYPE_1__ hsv_to_rgb (TYPE_2__) ; 

void backlight_effect_indicators_set_colors( uint8_t index, HS color )
{
    HSV hsv = { .h = color.h, .s = color.s, .v = g_config.brightness };
    RGB rgb = hsv_to_rgb( hsv );
    if ( index == 254 )
    {
        backlight_set_color_all( rgb.r, rgb.g, rgb.b );
    }
    else
    {
        backlight_set_color( index, rgb.r, rgb.g, rgb.b );

        // If the spacebar LED is the indicator,
        // do the same for the spacebar stabilizers
        if ( index == 36+0 ) // LC0
        {
#if defined(RGB_BACKLIGHT_ZEAL65)
            backlight_set_color( 36+7, rgb.r, rgb.g, rgb.b ); // LC7
            backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
#elif defined(RGB_BACKLIGHT_KOYU)
            backlight_set_color( 36+6, rgb.r, rgb.g, rgb.b ); // LC6
            backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
#elif defined(RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_M60_A)
            backlight_set_color( 36+6, rgb.r, rgb.g, rgb.b ); // LC6
            backlight_set_color( 54+13, rgb.r, rgb.g, rgb.b ); // LD13
            if ( g_config.use_7u_spacebar )
            {
                backlight_set_color( 54+14, rgb.r, rgb.g, rgb.b ); // LD14
            }
#endif
        }
    }
}