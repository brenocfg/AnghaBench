#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct power_supply {TYPE_1__* desc; int /*<<< orphan*/  use_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* external_power_changed ) (struct power_supply*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct power_supply*) ; 

void power_supply_external_power_changed(struct power_supply *psy)
{
	if (atomic_read(&psy->use_cnt) <= 0 ||
			!psy->desc->external_power_changed)
		return;

	psy->desc->external_power_changed(psy);
}