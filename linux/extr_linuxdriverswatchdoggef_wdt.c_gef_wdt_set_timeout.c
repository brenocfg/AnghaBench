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
 int bus_clk ; 
 unsigned int gef_wdt_count ; 
 unsigned int gef_wdt_timeout ; 

__attribute__((used)) static void gef_wdt_set_timeout(unsigned int timeout)
{
	/* maximum bus cycle count is 0xFFFFFFFF */
	if (timeout > 0xFFFFFFFF / bus_clk)
		timeout = 0xFFFFFFFF / bus_clk;

	/* Register only holds upper 24 bits, bit shifted into lower 24 */
	gef_wdt_count = (timeout * bus_clk) >> 8;
	gef_wdt_timeout = timeout;
}