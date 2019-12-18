#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int disable_after_timeout; int brightness; int effect; int effect_speed; int /*<<< orphan*/  color_1; int /*<<< orphan*/  disable_when_usb_suspended; } ;

/* Variables and functions */
 int /*<<< orphan*/  _get_color (int /*<<< orphan*/ *,int*) ; 
 TYPE_1__ g_config ; 
#define  id_brightness 133 
#define  id_color_1 132 
#define  id_disable_after_timeout 131 
#define  id_disable_when_usb_suspended 130 
#define  id_effect 129 
#define  id_effect_speed 128 

void backlight_config_get_value( uint8_t *data )
{
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_disable_when_usb_suspended:
        {
            *value_data = ( g_config.disable_when_usb_suspended ? 1 : 0 );
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
    }
}