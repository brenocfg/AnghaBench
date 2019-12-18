#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int n_members; TYPE_1__** members; } ;
struct TYPE_7__ {scalar_t__ opcfamily; scalar_t__ opcintype; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_opclass ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_AM_OID ; 
 int /*<<< orphan*/  CLAAMNAMENSP ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCatCacheList (TYPE_3__*) ; 
 TYPE_3__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
opfamily_can_sort_type(Oid opfamilyoid, Oid datatypeoid)
{
	bool		result = false;
	CatCList   *opclist;
	int			i;

	/*
	 * We search through all btree opclasses to see if one matches.  This is a
	 * bit inefficient but there is no better index available.  It also saves
	 * making an explicit check that the opfamily belongs to btree.
	 */
	opclist = SearchSysCacheList1(CLAAMNAMENSP, ObjectIdGetDatum(BTREE_AM_OID));

	for (i = 0; i < opclist->n_members; i++)
	{
		HeapTuple	classtup = &opclist->members[i]->tuple;
		Form_pg_opclass classform = (Form_pg_opclass) GETSTRUCT(classtup);

		if (classform->opcfamily == opfamilyoid &&
			classform->opcintype == datatypeoid)
		{
			result = true;
			break;
		}
	}

	ReleaseCatCacheList(opclist);

	return result;
}