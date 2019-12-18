#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nLockDeps; int nDeps; scalar_t__* lockDeps; scalar_t__* dependencies; } ;
typedef  TYPE_1__ TocEntry ;

/* Variables and functions */

__attribute__((used)) static bool
has_lock_conflicts(TocEntry *te1, TocEntry *te2)
{
	int			j,
				k;

	for (j = 0; j < te1->nLockDeps; j++)
	{
		for (k = 0; k < te2->nDeps; k++)
		{
			if (te1->lockDeps[j] == te2->dependencies[k])
				return true;
		}
	}
	return false;
}