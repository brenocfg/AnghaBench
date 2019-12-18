#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ndeps; TYPE_1__** deps; } ;
struct TYPE_6__ {int nattributes; scalar_t__ degree; } ;
typedef  int /*<<< orphan*/  StatisticExtInfo ;
typedef  TYPE_1__ MVDependency ;
typedef  TYPE_2__ MVDependencies ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int bms_num_members (int /*<<< orphan*/ *) ; 
 scalar_t__ dependency_is_fully_matched (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MVDependency *
find_strongest_dependency(StatisticExtInfo *stats, MVDependencies *dependencies,
						  Bitmapset *attnums)
{
	int			i;
	MVDependency *strongest = NULL;

	/* number of attnums in clauses */
	int			nattnums = bms_num_members(attnums);

	/*
	 * Iterate over the MVDependency items and find the strongest one from the
	 * fully-matched dependencies. We do the cheap checks first, before
	 * matching it against the attnums.
	 */
	for (i = 0; i < dependencies->ndeps; i++)
	{
		MVDependency *dependency = dependencies->deps[i];

		/*
		 * Skip dependencies referencing more attributes than available
		 * clauses, as those can't be fully matched.
		 */
		if (dependency->nattributes > nattnums)
			continue;

		if (strongest)
		{
			/* skip dependencies on fewer attributes than the strongest. */
			if (dependency->nattributes < strongest->nattributes)
				continue;

			/* also skip weaker dependencies when attribute count matches */
			if (strongest->nattributes == dependency->nattributes &&
				strongest->degree > dependency->degree)
				continue;
		}

		/*
		 * this dependency is stronger, but we must still check that it's
		 * fully matched to these attnums. We perform this check last as it's
		 * slightly more expensive than the previous checks.
		 */
		if (dependency_is_fully_matched(dependency, attnums))
			strongest = dependency; /* save new best match */
	}

	return strongest;
}