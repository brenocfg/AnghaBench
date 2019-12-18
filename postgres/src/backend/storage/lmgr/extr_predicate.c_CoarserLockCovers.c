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
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;

/* Variables and functions */
 scalar_t__ GetParentPredicateLockTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PredicateLockExists (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
CoarserLockCovers(const PREDICATELOCKTARGETTAG *newtargettag)
{
	PREDICATELOCKTARGETTAG targettag,
				parenttag;

	targettag = *newtargettag;

	/* check parents iteratively until no more */
	while (GetParentPredicateLockTag(&targettag, &parenttag))
	{
		targettag = parenttag;
		if (PredicateLockExists(&targettag))
			return true;
	}

	/* no more parents to check; lock is not covered */
	return false;
}