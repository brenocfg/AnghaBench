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
 int extif_clk_period ; 

__attribute__((used)) static inline unsigned long round_to_extif_ticks(unsigned long ps, int div)
{
	int bus_tick = extif_clk_period * div;
	return (ps + bus_tick - 1) / bus_tick * bus_tick;
}