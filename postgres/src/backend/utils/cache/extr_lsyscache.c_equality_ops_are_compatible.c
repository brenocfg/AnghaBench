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
struct TYPE_7__ {scalar_t__ amopmethod; int /*<<< orphan*/  amopfamily; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_amop ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 scalar_t__ BTREE_AM_OID ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HASH_AM_OID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCacheList (TYPE_3__*) ; 
 TYPE_3__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ op_in_opfamily (scalar_t__,int /*<<< orphan*/ ) ; 

bool
equality_ops_are_compatible(Oid opno1, Oid opno2)
{
	bool		result;
	CatCList   *catlist;
	int			i;

	/* Easy if they're the same operator */
	if (opno1 == opno2)
		return true;

	/*
	 * We search through all the pg_amop entries for opno1.
	 */
	catlist = SearchSysCacheList1(AMOPOPID, ObjectIdGetDatum(opno1));

	result = false;
	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple	op_tuple = &catlist->members[i]->tuple;
		Form_pg_amop op_form = (Form_pg_amop) GETSTRUCT(op_tuple);

		/* must be btree or hash */
		if (op_form->amopmethod == BTREE_AM_OID ||
			op_form->amopmethod == HASH_AM_OID)
		{
			if (op_in_opfamily(opno2, op_form->amopfamily))
			{
				result = true;
				break;
			}
		}
	}

	ReleaseSysCacheList(catlist);

	return result;
}