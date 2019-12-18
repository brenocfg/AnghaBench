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
struct TYPE_4__ {int /*<<< orphan*/  hasPseudoConstantQuals; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * extract_actual_clauses (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * order_qual_clauses (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
get_gating_quals(PlannerInfo *root, List *quals)
{
	/* No need to look if we know there are no pseudoconstants */
	if (!root->hasPseudoConstantQuals)
		return NIL;

	/* Sort into desirable execution order while still in RestrictInfo form */
	quals = order_qual_clauses(root, quals);

	/* Pull out any pseudoconstant quals from the RestrictInfo list */
	return extract_actual_clauses(quals, true);
}