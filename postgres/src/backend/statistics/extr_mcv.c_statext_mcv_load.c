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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MCVList ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_statistic_ext_data_stxdmcv ; 
 int /*<<< orphan*/  DatumGetByteaP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATEXTDATASTXOID ; 
 int /*<<< orphan*/  STATS_EXT_DEPENDENCIES ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * statext_mcv_deserialize (int /*<<< orphan*/ ) ; 

MCVList *
statext_mcv_load(Oid mvoid)
{
	MCVList    *result;
	bool		isnull;
	Datum		mcvlist;
	HeapTuple	htup = SearchSysCache1(STATEXTDATASTXOID, ObjectIdGetDatum(mvoid));

	if (!HeapTupleIsValid(htup))
		elog(ERROR, "cache lookup failed for statistics object %u", mvoid);

	mcvlist = SysCacheGetAttr(STATEXTDATASTXOID, htup,
							  Anum_pg_statistic_ext_data_stxdmcv, &isnull);

	if (isnull)
		elog(ERROR,
			 "requested statistic kind \"%c\" is not yet built for statistics object %u",
			 STATS_EXT_DEPENDENCIES, mvoid);

	result = statext_mcv_deserialize(DatumGetByteaP(mcvlist));

	ReleaseSysCache(htup);

	return result;
}