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
struct TYPE_4__ {int location; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int RTERangeTablePosn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* makeWholeRowVar (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  markVarForSelectPriv (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *
transformWholeRowRef(ParseState *pstate, RangeTblEntry *rte, int location)
{
	Var		   *result;
	int			vnum;
	int			sublevels_up;

	/* Find the RTE's rangetable location */
	vnum = RTERangeTablePosn(pstate, rte, &sublevels_up);

	/*
	 * Build the appropriate referencing node.  Note that if the RTE is a
	 * function returning scalar, we create just a plain reference to the
	 * function value, not a composite containing a single column.  This is
	 * pretty inconsistent at first sight, but it's what we've done
	 * historically.  One argument for it is that "rel" and "rel.*" mean the
	 * same thing for composite relations, so why not for scalar functions...
	 */
	result = makeWholeRowVar(rte, vnum, sublevels_up, true);

	/* location is not filled in by makeWholeRowVar */
	result->location = location;

	/* mark relation as requiring whole-row SELECT access */
	markVarForSelectPriv(pstate, result, rte);

	return (Node *) result;
}