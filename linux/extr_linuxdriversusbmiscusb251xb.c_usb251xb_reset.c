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
struct usb251xb {int /*<<< orphan*/  gpio_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void usb251xb_reset(struct usb251xb *hub, int state)
{
	if (!hub->gpio_reset)
		return;

	gpiod_set_value_cansleep(hub->gpio_reset, state);

	/* wait for hub recovery/stabilization */
	if (!state)
		usleep_range(500, 750);	/* >=500us at power on */
	else
		usleep_range(1, 10);	/* >=1us at power down */
}