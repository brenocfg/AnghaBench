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
typedef  int uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  index; int /*<<< orphan*/  color; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; int /*<<< orphan*/  color; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; int /*<<< orphan*/  color; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; int /*<<< orphan*/  color; } ;
struct TYPE_10__ {int disable_after_timeout; int brightness; int effect; int effect_speed; int* alphas_mods; int /*<<< orphan*/ * custom_color; TYPE_4__ layer_3_indicator; TYPE_3__ layer_2_indicator; TYPE_2__ layer_1_indicator; TYPE_1__ caps_lock_indicator; int /*<<< orphan*/  color_2; int /*<<< orphan*/  color_1; int /*<<< orphan*/  disable_hhkb_blocker_leds; int /*<<< orphan*/  disable_when_usb_suspended; int /*<<< orphan*/  use_iso_enter; int /*<<< orphan*/  use_7u_spacebar; int /*<<< orphan*/  use_split_right_shift; int /*<<< orphan*/  use_split_left_shift; int /*<<< orphan*/  use_split_backspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  _get_color (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  backlight_get_indicator_row_col (int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_5__ g_config ; 
#define  id_alphas_mods 150 
#define  id_brightness 149 
#define  id_caps_lock_indicator_color 148 
#define  id_caps_lock_indicator_row_col 147 
#define  id_color_1 146 
#define  id_color_2 145 
#define  id_custom_color 144 
#define  id_disable_after_timeout 143 
#define  id_disable_hhkb_blocker_leds 142 
#define  id_disable_when_usb_suspended 141 
#define  id_effect 140 
#define  id_effect_speed 139 
#define  id_layer_1_indicator_color 138 
#define  id_layer_1_indicator_row_col 137 
#define  id_layer_2_indicator_color 136 
#define  id_layer_2_indicator_row_col 135 
#define  id_layer_3_indicator_color 134 
#define  id_layer_3_indicator_row_col 133 
#define  id_use_7u_spacebar 132 
#define  id_use_iso_enter 131 
#define  id_use_split_backspace 130 
#define  id_use_split_left_shift 129 
#define  id_use_split_right_shift 128 

void backlight_config_get_value( uint8_t *data )
{
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_use_split_backspace:
        {
            *value_data = ( g_config.use_split_backspace ? 1 : 0 );
            break;
        }
        case id_use_split_left_shift:
        {
            *value_data = ( g_config.use_split_left_shift ? 1 : 0 );
            break;
        }
        case id_use_split_right_shift:
        {
            *value_data = ( g_config.use_split_right_shift ? 1 : 0 );
            break;
        }
        case id_use_7u_spacebar:
        {
            *value_data = ( g_config.use_7u_spacebar ? 1 : 0 );
            break;
        }
        case id_use_iso_enter:
        {
            *value_data = ( g_config.use_iso_enter ? 1 : 0 );
            break;
        }
        case id_disable_when_usb_suspended:
        {
            *value_data = ( g_config.disable_when_usb_suspended ? 1 : 0 );
            break;
        }
        case id_disable_hhkb_blocker_leds:
        {
            *value_data = ( g_config.disable_hhkb_blocker_leds ? 1 : 0 );
            break;
        }
        case id_disable_after_timeout:
        {
            *value_data = g_config.disable_after_timeout;
            break;
        }
        case id_brightness:
        {
            *value_data = g_config.brightness;
            break;
        }
        case id_effect:
        {
            *value_data = g_config.effect;
            break;
        }
        case id_effect_speed:
        {
            *value_data = g_config.effect_speed;
            break;
        }
        case id_color_1:
        {
            _get_color( &(g_config.color_1), value_data );
            break;
        }
        case id_color_2:
        {
            _get_color( &(g_config.color_2), value_data );
            break;
        }
        case id_caps_lock_indicator_color:
        {
            _get_color( &(g_config.caps_lock_indicator.color), value_data );
            break;
        }
        case id_caps_lock_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.caps_lock_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_layer_1_indicator_color:
        {
            _get_color( &(g_config.layer_1_indicator.color), value_data );
            break;
        }
        case id_layer_1_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.layer_1_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_layer_2_indicator_color:
        {
            _get_color( &(g_config.layer_2_indicator.color), value_data );
            break;
        }
        case id_layer_2_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.layer_2_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_layer_3_indicator_color:
        {
            _get_color( &(g_config.layer_3_indicator.color), value_data );
            break;
        }
        case id_layer_3_indicator_row_col:
        {
            backlight_get_indicator_row_col( g_config.layer_3_indicator.index, &(value_data[0]), &(value_data[1]) );
            break;
        }
        case id_alphas_mods:
        {
            for ( int i=0; i<5; i++ )
            {
                *(value_data+i*2) = g_config.alphas_mods[i] >> 8;
                *(value_data+i*2+1) = g_config.alphas_mods[i] & 0xFF;
            }
        }
#if defined(RGB_BACKLIGHT_M6_B)
        case id_custom_color:
        {
            uint8_t index = value_data[0];
            if ( index >= 0 && index <= 6 )
            {
                _get_color( &(g_config.custom_color[index]), &(value_data[1]) );
            }
        }
#endif
    }
}