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
struct gb_power_supply {int update_interval; } ;

/* Variables and functions */
 int update_interval_max ; 

__attribute__((used)) static void next_interval(struct gb_power_supply *gbpsy)
{
	if (gbpsy->update_interval == update_interval_max)
		return;

	/* do some exponential back-off in the update interval */
	gbpsy->update_interval *= 2;
	if (gbpsy->update_interval > update_interval_max)
		gbpsy->update_interval = update_interval_max;
}