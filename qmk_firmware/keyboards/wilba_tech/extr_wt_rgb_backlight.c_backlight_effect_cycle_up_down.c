#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int effect_speed; scalar_t__ use_7u_spacebar; int /*<<< orphan*/  brightness; } ;
struct TYPE_10__ {int h; int s; int /*<<< orphan*/  v; } ;
struct TYPE_9__ {int y; } ;
struct TYPE_8__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ RGB ;
typedef  TYPE_2__ Point ;
typedef  TYPE_3__ HSV ;

/* Variables and functions */
 int BACKLIGHT_LED_COUNT ; 
 int /*<<< orphan*/  backlight_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ g_config ; 
 int* g_key_hit ; 
 int g_tick ; 
 TYPE_1__ hsv_to_rgb (TYPE_3__) ; 
 int /*<<< orphan*/  map_led_to_point (int,TYPE_2__*) ; 

void backlight_effect_cycle_up_down(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;
    HSV hsv = { .h = 0, .s = 255, .v = g_config.brightness };
    RGB rgb;
    Point point;
    for ( int i=0; i<BACKLIGHT_LED_COUNT; i++ )
    {
        uint16_t offset2 = g_key_hit[i]<<2;
#if !defined(RGB_BACKLIGHT_HS60) && !defined(RGB_BACKLIGHT_NK65)
        // stabilizer LEDs use spacebar hits
        if ( i == 36+6 || i == 54+13 || // LC6, LD13
                ( g_config.use_7u_spacebar && i == 54+14 ) ) // LD14
        {
            offset2 = g_key_hit[36+0]<<2;
        }
#endif
        offset2 = (offset2<=63) ? (63-offset2) : 0;

        map_led_to_point( i, &point );
        // Relies on hue being 8-bit and wrapping
        hsv.h = point.y + offset + offset2;
        rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}