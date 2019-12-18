#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * partexprs; } ;
struct TYPE_5__ {scalar_t__ clause; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  TYPE_2__ RelOptInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_notclausearg (int /*<<< orphan*/ *) ; 
 scalar_t__ is_notclause (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
matches_boolean_partition_clause(RestrictInfo *rinfo,
								 RelOptInfo *partrel, int partkeycol)
{
	Node	   *clause = (Node *) rinfo->clause;
	Node	   *partexpr = (Node *) linitial(partrel->partexprs[partkeycol]);

	/* Direct match? */
	if (equal(partexpr, clause))
		return true;
	/* NOT clause? */
	else if (is_notclause(clause))
	{
		Node	   *arg = (Node *) get_notclausearg((Expr *) clause);

		if (equal(partexpr, arg))
			return true;
	}

	return false;
}