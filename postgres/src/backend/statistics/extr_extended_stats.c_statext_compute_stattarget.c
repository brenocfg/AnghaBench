#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* attr; } ;
typedef  TYPE_2__ VacAttrStats ;
struct TYPE_4__ {int attstattarget; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int default_statistics_target ; 

__attribute__((used)) static int
statext_compute_stattarget(int stattarget, int nattrs, VacAttrStats **stats)
{
	int	i;

	/*
	 * If there's statistics target set for the statistics object, use it.
	 * It may be set to 0 which disables building of that statistic.
	 */
	if (stattarget >= 0)
		return stattarget;

	/*
	 * The target for the statistics object is set to -1, in which case we
	 * look at the maximum target set for any of the attributes the object
	 * is defined on.
	 */
	for (i = 0; i < nattrs; i++)
	{
		/* keep the maximmum statistics target */
		if (stats[i]->attr->attstattarget > stattarget)
			stattarget = stats[i]->attr->attstattarget;
	}

	/*
	 * If the value is still negative (so neither the statistics object nor
	 * any of the columns have custom statistics target set), use the global
	 * default target.
	 */
	if (stattarget < 0)
		stattarget = default_statistics_target;

	/* As this point we should have a valid statistics target. */
	Assert((stattarget >= 0) && (stattarget <= 10000));

	return stattarget;
}