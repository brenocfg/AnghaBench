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
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_statistic_ext_data_stxddependencies ; 
 int /*<<< orphan*/  Anum_pg_statistic_ext_data_stxdmcv ; 
 int /*<<< orphan*/  Anum_pg_statistic_ext_data_stxdndistinct ; 
 int /*<<< orphan*/  ERROR ; 
#define  STATS_EXT_DEPENDENCIES 130 
#define  STATS_EXT_MCV 129 
#define  STATS_EXT_NDISTINCT 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
statext_is_kind_built(HeapTuple htup, char type)
{
	AttrNumber	attnum;

	switch (type)
	{
		case STATS_EXT_NDISTINCT:
			attnum = Anum_pg_statistic_ext_data_stxdndistinct;
			break;

		case STATS_EXT_DEPENDENCIES:
			attnum = Anum_pg_statistic_ext_data_stxddependencies;
			break;

		case STATS_EXT_MCV:
			attnum = Anum_pg_statistic_ext_data_stxdmcv;
			break;

		default:
			elog(ERROR, "unexpected statistics type requested: %d", type);
	}

	return !heap_attisnull(htup, attnum, NULL);
}