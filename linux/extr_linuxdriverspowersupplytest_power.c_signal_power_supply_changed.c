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
struct power_supply {int dummy; } ;

/* Variables and functions */
 scalar_t__ module_initialized ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 

__attribute__((used)) static inline void signal_power_supply_changed(struct power_supply *psy)
{
	if (module_initialized)
		power_supply_changed(psy);
}