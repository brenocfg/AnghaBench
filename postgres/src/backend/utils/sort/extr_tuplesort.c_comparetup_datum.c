#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_6__* sortKeys; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_10__ {scalar_t__ abbrev_converter; } ;
struct TYPE_9__ {int /*<<< orphan*/  isnull1; int /*<<< orphan*/  tuple; int /*<<< orphan*/  datum1; } ;
typedef  TYPE_2__ SortTuple ;

/* Variables and functions */
 int ApplySortAbbrevFullComparator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int ApplySortComparator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comparetup_datum(const SortTuple *a, const SortTuple *b, Tuplesortstate *state)
{
	int			compare;

	compare = ApplySortComparator(a->datum1, a->isnull1,
								  b->datum1, b->isnull1,
								  state->sortKeys);
	if (compare != 0)
		return compare;

	/* if we have abbreviations, then "tuple" has the original value */

	if (state->sortKeys->abbrev_converter)
		compare = ApplySortAbbrevFullComparator(PointerGetDatum(a->tuple), a->isnull1,
												PointerGetDatum(b->tuple), b->isnull1,
												state->sortKeys);

	return compare;
}