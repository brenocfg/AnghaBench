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
struct gred_sched {TYPE_1__** tab; scalar_t__ red_flags; } ;
struct TYPE_2__ {scalar_t__ red_flags; } ;

/* Variables and functions */
 unsigned int MAX_DPs ; 

__attribute__((used)) static bool gred_per_vq_red_flags_used(struct gred_sched *table)
{
	unsigned int i;

	/* Local per-vq flags couldn't have been set unless global are 0 */
	if (table->red_flags)
		return false;
	for (i = 0; i < MAX_DPs; i++)
		if (table->tab[i] && table->tab[i]->red_flags)
			return true;
	return false;
}