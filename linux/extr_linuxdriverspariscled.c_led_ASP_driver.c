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

/* Variables and functions */
 int /*<<< orphan*/  LED_DATA_REG ; 
 unsigned char LED_STROBE ; 
 int /*<<< orphan*/  gsc_writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void led_ASP_driver(unsigned char leds)
{
	int i;

	leds = ~leds;
	for (i = 0; i < 8; i++) {
		unsigned char value;
		value = (leds & 0x80) >> 7;
		gsc_writeb( value,		 LED_DATA_REG );
		gsc_writeb( value | LED_STROBE,	 LED_DATA_REG );
		leds <<= 1;
	}
}