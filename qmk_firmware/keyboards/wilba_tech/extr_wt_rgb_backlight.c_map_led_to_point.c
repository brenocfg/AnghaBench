#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  use_split_right_shift; int /*<<< orphan*/  use_7u_spacebar; int /*<<< orphan*/  use_split_left_shift; int /*<<< orphan*/  use_iso_enter; int /*<<< orphan*/  use_split_backspace; } ;
struct TYPE_4__ {int x; int y; } ;
typedef  TYPE_1__ Point ;

/* Variables and functions */
 TYPE_3__ g_config ; 
 int /*<<< orphan*/ * g_map_led_to_point ; 
 void* pgm_read_byte (size_t*) ; 

void map_led_to_point( uint8_t index, Point *point )
{
    // Slightly messy way to get Point structs out of progmem.
    uint8_t *addr = (uint8_t*)&g_map_led_to_point[index];
    point->x = pgm_read_byte(addr);
    point->y = pgm_read_byte(addr+1);

#if defined(RGB_BACKLIGHT_M6_B) || defined(RGB_BACKLIGHT_HS60) || defined(RGB_BACKLIGHT_NK65)
    return;
#endif

    switch (index)
    {
        case 18+4: // LB4A
            if ( g_config.use_split_backspace )
                point->x -= 8;
            break;
#if defined(RGB_BACKLIGHT_ZEAL60)
        case 18+14: // LB14A
            if ( g_config.use_iso_enter )
                point->y += 8; // extremely pedantic
            break;
        case 54+5: // LD5A
            if ( !g_config.use_iso_enter )
                point->x -= 10;
            break;
        case 36+16: // LC16A
            if ( !g_config.use_split_left_shift )
                point->x += 8;
            break;
#endif
#if defined(RGB_BACKLIGHT_ZEAL60) || defined(RGB_BACKLIGHT_M60_A)
        case 36+0: // LC0A
            if ( g_config.use_7u_spacebar )
                point->x += 10;
            break;
        case 36+6: // LC6A
            if ( g_config.use_7u_spacebar )
                point->x += 4;
            break;
        case 54+7: // LD7A
            if ( !g_config.use_split_right_shift )
                point->x -= 8;
            break;
#endif
    }
}