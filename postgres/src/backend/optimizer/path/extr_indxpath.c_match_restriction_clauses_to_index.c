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
struct TYPE_4__ {int /*<<< orphan*/  indrestrictinfo; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ IndexOptInfo ;
typedef  int /*<<< orphan*/  IndexClauseSet ;

/* Variables and functions */
 int /*<<< orphan*/  match_clauses_to_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
match_restriction_clauses_to_index(PlannerInfo *root,
								   IndexOptInfo *index,
								   IndexClauseSet *clauseset)
{
	/* We can ignore clauses that are implied by the index predicate */
	match_clauses_to_index(root, index->indrestrictinfo, index, clauseset);
}