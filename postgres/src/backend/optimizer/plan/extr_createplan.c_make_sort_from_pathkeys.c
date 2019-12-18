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
typedef  int /*<<< orphan*/  Sort ;
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * make_sort (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * prepare_sort_from_pathkeys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int**) ; 

__attribute__((used)) static Sort *
make_sort_from_pathkeys(Plan *lefttree, List *pathkeys, Relids relids)
{
	int			numsortkeys;
	AttrNumber *sortColIdx;
	Oid		   *sortOperators;
	Oid		   *collations;
	bool	   *nullsFirst;

	/* Compute sort column info, and adjust lefttree as needed */
	lefttree = prepare_sort_from_pathkeys(lefttree, pathkeys,
										  relids,
										  NULL,
										  false,
										  &numsortkeys,
										  &sortColIdx,
										  &sortOperators,
										  &collations,
										  &nullsFirst);

	/* Now build the Sort node */
	return make_sort(lefttree, numsortkeys,
					 sortColIdx, sortOperators,
					 collations, nullsFirst);
}