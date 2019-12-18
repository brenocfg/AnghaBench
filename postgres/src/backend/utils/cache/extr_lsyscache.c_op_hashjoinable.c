#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hash_proc; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_5__ {int oprcanhash; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_operator ;

/* Variables and functions */
 scalar_t__ ARRAY_EQ_OP ; 
 scalar_t__ F_HASH_ARRAY ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPECACHE_HASH_PROC ; 
 TYPE_1__* lookup_type_cache (scalar_t__,int /*<<< orphan*/ ) ; 

bool
op_hashjoinable(Oid opno, Oid inputtype)
{
	bool		result = false;
	HeapTuple	tp;
	TypeCacheEntry *typentry;

	/* As in op_mergejoinable, let the typcache handle the hard cases */
	/* Eventually we'll need a similar case for record_eq ... */
	if (opno == ARRAY_EQ_OP)
	{
		typentry = lookup_type_cache(inputtype, TYPECACHE_HASH_PROC);
		if (typentry->hash_proc == F_HASH_ARRAY)
			result = true;
	}
	else
	{
		/* For all other operators, rely on pg_operator.oprcanhash */
		tp = SearchSysCache1(OPEROID, ObjectIdGetDatum(opno));
		if (HeapTupleIsValid(tp))
		{
			Form_pg_operator optup = (Form_pg_operator) GETSTRUCT(tp);

			result = optup->oprcanhash;
			ReleaseSysCache(tp);
		}
	}
	return result;
}