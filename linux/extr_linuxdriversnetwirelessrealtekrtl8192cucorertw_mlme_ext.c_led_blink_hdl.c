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
typedef  int /*<<< orphan*/  u8 ;
struct LedBlink_param {int dummy; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_PARAMETERS_ERROR ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 

u8 led_blink_hdl(_adapter *padapter, unsigned char *pbuf)
{
	struct LedBlink_param *ledBlink_param;

	if(!pbuf)
		return H2C_PARAMETERS_ERROR;

	ledBlink_param = (struct LedBlink_param *)pbuf;

	#ifdef CONFIG_LED_HANDLED_BY_CMD_THREAD
	BlinkHandler(ledBlink_param->pLed);
	#endif

	return 	H2C_SUCCESS;
}