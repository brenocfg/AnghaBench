#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_7__ {int enumtypid; } ;
struct TYPE_6__ {TYPE_1__* flinfo; } ;
struct TYPE_5__ {void* fn_extra; } ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* FunctionCallInfo ;
typedef  TYPE_3__* Form_pg_enum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENUMOID ; 
 int /*<<< orphan*/  ERRCODE_INVALID_BINARY_REPRESENTATION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int compare_values_of_enum (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int /*<<< orphan*/ * lookup_type_cache (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enum_cmp_internal(Oid arg1, Oid arg2, FunctionCallInfo fcinfo)
{
	TypeCacheEntry *tcache;

	/*
	 * We don't need the typcache except in the hopefully-uncommon case that
	 * one or both Oids are odd.  This means that cursory testing of code that
	 * fails to pass flinfo to an enum comparison function might not disclose
	 * the oversight.  To make such errors more obvious, Assert that we have a
	 * place to cache even when we take a fast-path exit.
	 */
	Assert(fcinfo->flinfo != NULL);

	/* Equal OIDs are equal no matter what */
	if (arg1 == arg2)
		return 0;

	/* Fast path: even-numbered Oids are known to compare correctly */
	if ((arg1 & 1) == 0 && (arg2 & 1) == 0)
	{
		if (arg1 < arg2)
			return -1;
		else
			return 1;
	}

	/* Locate the typcache entry for the enum type */
	tcache = (TypeCacheEntry *) fcinfo->flinfo->fn_extra;
	if (tcache == NULL)
	{
		HeapTuple	enum_tup;
		Form_pg_enum en;
		Oid			typeoid;

		/* Get the OID of the enum type containing arg1 */
		enum_tup = SearchSysCache1(ENUMOID, ObjectIdGetDatum(arg1));
		if (!HeapTupleIsValid(enum_tup))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_BINARY_REPRESENTATION),
					 errmsg("invalid internal value for enum: %u",
							arg1)));
		en = (Form_pg_enum) GETSTRUCT(enum_tup);
		typeoid = en->enumtypid;
		ReleaseSysCache(enum_tup);
		/* Now locate and remember the typcache entry */
		tcache = lookup_type_cache(typeoid, 0);
		fcinfo->flinfo->fn_extra = (void *) tcache;
	}

	/* The remaining comparison logic is in typcache.c */
	return compare_values_of_enum(tcache, arg1, arg2);
}