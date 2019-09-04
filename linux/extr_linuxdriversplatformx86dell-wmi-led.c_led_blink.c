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
 int /*<<< orphan*/  CMD_LED_BLINK ; 
 int /*<<< orphan*/  DEVICE_ID_PANEL_BACK ; 
 int /*<<< orphan*/  INTERFACE_ERROR ; 
 int dell_led_perform_fn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static int led_blink(unsigned char on_eighths, unsigned char off_eighths)
{
	return dell_led_perform_fn(5,	/* Length of command */
		INTERFACE_ERROR,	/* Init to  INTERFACE_ERROR */
		DEVICE_ID_PANEL_BACK,	/* Device ID */
		CMD_LED_BLINK,		/* Command */
		on_eighths,		/* blink on in eigths of a second */
		off_eighths);		/* blink off in eights of a second */
}