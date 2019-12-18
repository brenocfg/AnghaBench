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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  AND_EXPR ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/ * generate_partition_qual (int /*<<< orphan*/ ) ; 
 scalar_t__ get_rel_relispartition (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeBoolExpr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Expr *
get_partition_qual_relid(Oid relid)
{
	Expr	   *result = NULL;

	/* Do the work only if this relation exists and is a partition. */
	if (get_rel_relispartition(relid))
	{
		Relation	rel = relation_open(relid, AccessShareLock);
		List	   *and_args;

		and_args = generate_partition_qual(rel);

		/* Convert implicit-AND list format to boolean expression */
		if (and_args == NIL)
			result = NULL;
		else if (list_length(and_args) > 1)
			result = makeBoolExpr(AND_EXPR, and_args, -1);
		else
			result = linitial(and_args);

		/* Keep the lock, to allow safe deparsing against the rel by caller. */
		relation_close(rel, NoLock);
	}

	return result;
}