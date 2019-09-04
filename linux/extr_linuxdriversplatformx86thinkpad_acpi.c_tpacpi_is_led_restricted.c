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
 unsigned int const TPACPI_SAFE_LEDS ; 

__attribute__((used)) static inline bool tpacpi_is_led_restricted(const unsigned int led)
{
#ifdef CONFIG_THINKPAD_ACPI_UNSAFE_LEDS
	return false;
#else
	return (1U & (TPACPI_SAFE_LEDS >> led)) == 0;
#endif
}