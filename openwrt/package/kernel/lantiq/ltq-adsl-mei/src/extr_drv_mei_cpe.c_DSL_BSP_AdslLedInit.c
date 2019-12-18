#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct led_config_param {int led; int source; void* operation_mask; } ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  scalar_t__ DSL_DEV_LedType_t ;
typedef  scalar_t__ DSL_DEV_LedId_t ;
typedef  scalar_t__ DSL_DEV_LedHandler_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 void* CONFIG_OPERATION_UPDATE_SOURCE ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 scalar_t__ DSL_LED_DATA_ID ; 
 scalar_t__ DSL_LED_DATA_TYPE ; 
 scalar_t__ DSL_LED_HD_FW ; 
 scalar_t__ DSL_LED_LINK_ID ; 
 scalar_t__ DSL_LED_LINK_TYPE ; 

DSL_DEV_MeiError_t
DSL_BSP_AdslLedInit (DSL_DEV_Device_t * dev,
			  DSL_DEV_LedId_t led_number,
			  DSL_DEV_LedType_t type,
			  DSL_DEV_LedHandler_t handler)
{
#if 0
        struct led_config_param param;
        if (led_number == DSL_LED_LINK_ID && type == DSL_LED_LINK_TYPE && handler == /*DSL_LED_HD_CPU*/DSL_LED_HD_FW) {
                param.operation_mask = CONFIG_OPERATION_UPDATE_SOURCE;
                param.led = 0x01;
                param.source = 0x01;
//                bsp_led_config (&param);

        } else if (led_number == DSL_LED_DATA_ID && type == DSL_LED_DATA_TYPE && (handler == DSL_LED_HD_FW)) {
                param.operation_mask = CONFIG_OPERATION_UPDATE_SOURCE;
                param.led = 0x02;
                param.source = 0x02;
//                bsp_led_config (&param);
        }
#endif
        return DSL_DEV_MEI_ERR_SUCCESS;
}