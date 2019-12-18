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
typedef  int /*<<< orphan*/  SortGroupClause ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eqop ; 
 int /*<<< orphan*/  hashable ; 
 int /*<<< orphan*/  nulls_first ; 
 int /*<<< orphan*/  sortop ; 
 int /*<<< orphan*/  tleSortGroupRef ; 

__attribute__((used)) static bool
_equalSortGroupClause(const SortGroupClause *a, const SortGroupClause *b)
{
	COMPARE_SCALAR_FIELD(tleSortGroupRef);
	COMPARE_SCALAR_FIELD(eqop);
	COMPARE_SCALAR_FIELD(sortop);
	COMPARE_SCALAR_FIELD(nulls_first);
	COMPARE_SCALAR_FIELD(hashable);

	return true;
}