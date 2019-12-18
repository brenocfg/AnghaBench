#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_9__ {int h; int s; } ;
struct TYPE_8__ {int h; int s; } ;
struct TYPE_12__ {int /*<<< orphan*/  brightness; TYPE_2__ color_2; TYPE_1__ color_1; } ;
struct TYPE_11__ {int h; int s; int /*<<< orphan*/  v; } ;
struct TYPE_10__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_3__ RGB ;
typedef  TYPE_4__ HSV ;

/* Variables and functions */
 int BACKLIGHT_LED_COUNT ; 
 int /*<<< orphan*/  backlight_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ g_config ; 
 int g_tick ; 
 TYPE_3__ hsv_to_rgb (TYPE_4__) ; 
 int rand () ; 

void backlight_effect_raindrops(bool initialize)
{
    int16_t h1 = g_config.color_1.h;
    int16_t h2 = g_config.color_2.h;
    int16_t deltaH = h2 - h1;
    deltaH /= 4;

    // Take the shortest path between hues
    if ( deltaH > 127 )
    {
        deltaH -= 256;
    }
    else if ( deltaH < -127 )
    {
        deltaH += 256;
    }

    int16_t s1 = g_config.color_1.s;
    int16_t s2 = g_config.color_2.s;
    int16_t deltaS = ( s2 - s1 ) / 4;

    HSV hsv;
    RGB rgb;

    // Change one LED every tick
    uint8_t led_to_change = ( g_tick & 0x000 ) == 0 ? rand() % BACKLIGHT_LED_COUNT : 255;

    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        // If initialize, all get set to random colors
        // If not, all but one will stay the same as before.
        if ( initialize || i == led_to_change )
        {
            hsv.h = h1 + ( deltaH * ( rand() & 0x03 ) );
            hsv.s = s1 + ( deltaS * ( rand() & 0x03 ) );
            // Override brightness with global brightness control
            hsv.v = g_config.brightness;;

            rgb = hsv_to_rgb( hsv );
            backlight_set_color( i, rgb.r, rgb.g, rgb.b );
        }
    }
}