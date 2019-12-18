#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int effect_speed; int /*<<< orphan*/  brightness; scalar_t__ use_7u_spacebar; } ;
struct TYPE_7__ {int s; int /*<<< orphan*/  v; int /*<<< orphan*/  h; } ;
struct TYPE_6__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ RGB ;
typedef  TYPE_2__ HSV ;

/* Variables and functions */
 int BACKLIGHT_LED_COUNT ; 
 int /*<<< orphan*/  backlight_set_color (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ g_config ; 
 int* g_key_hit ; 
 int g_tick ; 
 TYPE_1__ hsv_to_rgb (TYPE_2__) ; 

void backlight_effect_cycle_all(void)
{
    uint8_t offset = ( g_tick << g_config.effect_speed ) & 0xFF;

    // Relies on hue being 8-bit and wrapping
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

        HSV hsv = { .h = offset+offset2, .s = 255, .v = g_config.brightness };
        RGB rgb = hsv_to_rgb( hsv );
        backlight_set_color( i, rgb.r, rgb.g, rgb.b );
    }
}