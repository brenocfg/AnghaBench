#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* resname; scalar_t__ resno; int /*<<< orphan*/  expr; } ;
typedef  TYPE_1__ TargetEntry ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_KIND_UPDATE_TARGET ; 
 int /*<<< orphan*/  transformAssignedExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 

void
updateTargetListEntry(ParseState *pstate,
					  TargetEntry *tle,
					  char *colname,
					  int attrno,
					  List *indirection,
					  int location)
{
	/* Fix up expression as needed */
	tle->expr = transformAssignedExpr(pstate,
									  tle->expr,
									  EXPR_KIND_UPDATE_TARGET,
									  colname,
									  attrno,
									  indirection,
									  location);

	/*
	 * Set the resno to identify the target column --- the rewriter and
	 * planner depend on this.  We also set the resname to identify the target
	 * column, but this is only for debugging purposes; it should not be
	 * relied on.  (In particular, it might be out of date in a stored rule.)
	 */
	tle->resno = (AttrNumber) attrno;
	tle->resname = colname;
}