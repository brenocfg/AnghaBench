#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_11__ {int h; int s; } ;
struct TYPE_10__ {int h; int s; } ;
struct TYPE_15__ {TYPE_2__ color_1; int /*<<< orphan*/  brightness; TYPE_1__ color_2; } ;
struct TYPE_14__ {int h; int s; int /*<<< orphan*/  v; } ;
struct TYPE_13__ {int y; } ;
struct TYPE_12__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_3__ RGB ;
typedef  TYPE_4__ Point ;
typedef  TYPE_5__ HSV ;

/* Variables and functions */
 int BACKLIGHT_LED_COUNT ; 
 int /*<<< orphan*/  backlight_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ g_config ; 
 TYPE_3__ hsv_to_rgb (TYPE_5__) ; 
 int /*<<< orphan*/  map_led_to_point (int,TYPE_4__*) ; 

void backlight_effect_gradient_up_down(void)
{
    int16_t h1 = g_config.color_1.h;
    int16_t h2 = g_config.color_2.h;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }
    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = g_config.color_1.s;
    int16_t s2 = g_config.color_2.s;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        map_led_to_point( i, &point );
        // The y range will be 0..64, map this to 0..4
        uint8_t y = (point.y>>4);
        // Relies on hue being 8-bit and wrapping
        hsv.h = g_config.color_1.h + ( deltaH * y );
        hsv.s = g_config.color_1.s + ( deltaS * y );
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}