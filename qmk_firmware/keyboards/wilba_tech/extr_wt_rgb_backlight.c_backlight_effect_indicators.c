#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int index; int /*<<< orphan*/  color; } ;
struct TYPE_8__ {int index; int /*<<< orphan*/  color; } ;
struct TYPE_7__ {int index; int /*<<< orphan*/  color; } ;
struct TYPE_6__ {int index; int /*<<< orphan*/  color; } ;
struct TYPE_10__ {TYPE_4__ layer_1_indicator; TYPE_3__ layer_2_indicator; TYPE_2__ layer_3_indicator; TYPE_1__ caps_lock_indicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS31FL3733_set_color (int,int,int,int) ; 
 scalar_t__ IS_LAYER_ON (int) ; 
 scalar_t__ IS_LED_ON (int,int) ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  backlight_effect_indicators_set_colors (int,int /*<<< orphan*/ ) ; 
 TYPE_5__ g_config ; 
 int g_indicator_state ; 

void backlight_effect_indicators(void)
{
    if ( g_config.caps_lock_indicator.index != 255 &&
            ( g_indicator_state & (1<<USB_LED_CAPS_LOCK) ) )
    {
        backlight_effect_indicators_set_colors( g_config.caps_lock_indicator.index, g_config.caps_lock_indicator.color );
    }

#if defined(RGB_BACKLIGHT_NK65)
    if ( IS_LED_ON(g_indicator_state, USB_LED_CAPS_LOCK) ) {
        IS31FL3733_set_color( 7+64-1, 0, 255, 0 );
    } else {
        IS31FL3733_set_color( 7+64-1, 0, 0, 0 );
    }
    if ( IS_LAYER_ON(1) ) {
        IS31FL3733_set_color( 6+64-1, 255, 0, 255 );
    } else if ( IS_LAYER_ON(2) ) {
        IS31FL3733_set_color( 6+64-1, 0, 255, 0 );
    } else {
        IS31FL3733_set_color( 6+64-1, 0, 0, 0 );
    }
#endif

    // This if/else if structure allows higher layers to
    // override lower ones. If we set layer 3's indicator
    // to none, then it will NOT show layer 2 or layer 1
    // indicators, even if those layers are on via the
    // MO13/MO23 Fn combo magic.
    //
    // Basically we want to handle the case where layer 3 is
    // still the backlight configuration layer and we don't
    // want "all LEDs" indicators hiding the backlight effect,
    // but still allow end users to do whatever they want.
    if ( IS_LAYER_ON(3) )
    {
        if ( g_config.layer_3_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_3_indicator.index, g_config.layer_3_indicator.color );
        }
    }
    else if ( IS_LAYER_ON(2) )
    {
        if ( g_config.layer_2_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_2_indicator.index, g_config.layer_2_indicator.color );
        }
    }
    else if ( IS_LAYER_ON(1) )
    {
        if ( g_config.layer_1_indicator.index != 255 )
        {
            backlight_effect_indicators_set_colors( g_config.layer_1_indicator.index, g_config.layer_1_indicator.color );
        }
    }
}