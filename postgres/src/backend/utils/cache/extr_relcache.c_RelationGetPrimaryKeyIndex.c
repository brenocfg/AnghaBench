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
struct TYPE_4__ {int /*<<< orphan*/  rd_pkindex; int /*<<< orphan*/  rd_indexvalid; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RelationGetIndexList (TYPE_1__*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 

Oid
RelationGetPrimaryKeyIndex(Relation relation)
{
	List	   *ilist;

	if (!relation->rd_indexvalid)
	{
		/* RelationGetIndexList does the heavy lifting. */
		ilist = RelationGetIndexList(relation);
		list_free(ilist);
		Assert(relation->rd_indexvalid);
	}

	return relation->rd_pkindex;
}