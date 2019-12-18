#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_17__ {TYPE_1__* flinfo; } ;
struct TYPE_16__ {int keysize; int entrysize; } ;
struct TYPE_12__ {int /*<<< orphan*/  f_total_time; } ;
struct TYPE_15__ {TYPE_11__ f_counts; } ;
struct TYPE_14__ {int /*<<< orphan*/  f_start; int /*<<< orphan*/  save_total; int /*<<< orphan*/  save_f_total_time; TYPE_11__* fs; } ;
struct TYPE_13__ {scalar_t__ fn_stats; int /*<<< orphan*/  fn_oid; } ;
typedef  int /*<<< orphan*/  PgStat_FunctionCounts ;
typedef  TYPE_2__ PgStat_FunctionCallUsage ;
typedef  TYPE_3__ PgStat_BackendFunctionEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ HASHCTL ;
typedef  TYPE_5__* FunctionCallInfo ;

/* Variables and functions */
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PGSTAT_FUNCTION_HASH_SIZE ; 
 scalar_t__ hash_create (char*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 TYPE_3__* hash_search (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pgStatFunctions ; 
 scalar_t__ pgstat_track_functions ; 
 int /*<<< orphan*/  total_func_time ; 

void
pgstat_init_function_usage(FunctionCallInfo fcinfo,
						   PgStat_FunctionCallUsage *fcu)
{
	PgStat_BackendFunctionEntry *htabent;
	bool		found;

	if (pgstat_track_functions <= fcinfo->flinfo->fn_stats)
	{
		/* stats not wanted */
		fcu->fs = NULL;
		return;
	}

	if (!pgStatFunctions)
	{
		/* First time through - initialize function stat table */
		HASHCTL		hash_ctl;

		memset(&hash_ctl, 0, sizeof(hash_ctl));
		hash_ctl.keysize = sizeof(Oid);
		hash_ctl.entrysize = sizeof(PgStat_BackendFunctionEntry);
		pgStatFunctions = hash_create("Function stat entries",
									  PGSTAT_FUNCTION_HASH_SIZE,
									  &hash_ctl,
									  HASH_ELEM | HASH_BLOBS);
	}

	/* Get the stats entry for this function, create if necessary */
	htabent = hash_search(pgStatFunctions, &fcinfo->flinfo->fn_oid,
						  HASH_ENTER, &found);
	if (!found)
		MemSet(&htabent->f_counts, 0, sizeof(PgStat_FunctionCounts));

	fcu->fs = &htabent->f_counts;

	/* save stats for this function, later used to compensate for recursion */
	fcu->save_f_total_time = htabent->f_counts.f_total_time;

	/* save current backend-wide total time */
	fcu->save_total = total_func_time;

	/* get clock time as of function start */
	INSTR_TIME_SET_CURRENT(fcu->f_start);
}