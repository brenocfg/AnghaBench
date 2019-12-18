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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_GPIO_INPUT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_PULLUP ; 
 int /*<<< orphan*/  onewire_reset_search (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_gpio_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void onewire_init(uint8_t pin)
{
	// pinMode(pin, INPUT);
  platform_gpio_mode(pin, PLATFORM_GPIO_INPUT, PLATFORM_GPIO_PULLUP);
#if ONEWIRE_SEARCH
	onewire_reset_search(pin);
#endif
}