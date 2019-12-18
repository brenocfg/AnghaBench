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
 int /*<<< orphan*/  Assert (int) ; 
 int GET_PREDICATELOCKTARGETTAG_TYPE (int /*<<< orphan*/  const) ; 
#define  PREDLOCKTAG_PAGE 130 
#define  PREDLOCKTAG_RELATION 129 
#define  PREDLOCKTAG_TUPLE 128 
 int max_predicate_locks_per_page ; 
 int max_predicate_locks_per_relation ; 
 int max_predicate_locks_per_xact ; 

__attribute__((used)) static int
MaxPredicateChildLocks(const PREDICATELOCKTARGETTAG *tag)
{
	switch (GET_PREDICATELOCKTARGETTAG_TYPE(*tag))
	{
		case PREDLOCKTAG_RELATION:
			return max_predicate_locks_per_relation < 0
				? (max_predicate_locks_per_xact
				   / (-max_predicate_locks_per_relation)) - 1
				: max_predicate_locks_per_relation;

		case PREDLOCKTAG_PAGE:
			return max_predicate_locks_per_page;

		case PREDLOCKTAG_TUPLE:

			/*
			 * not reachable: nothing is finer-granularity than a tuple, so we
			 * should never try to promote to it.
			 */
			Assert(false);
			return 0;
	}

	/* not reachable */
	Assert(false);
	return 0;
}