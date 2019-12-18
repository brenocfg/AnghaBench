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
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ int64 ;
struct TYPE_5__ {int use_pagemode; scalar_t__ tsm_state; } ;
struct TYPE_4__ {scalar_t__ doneblocks; int /*<<< orphan*/  lt; scalar_t__ ntuples; int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ SystemRowsSamplerData ;
typedef  TYPE_2__ SampleScanState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TABLESAMPLE_ARGUMENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
system_rows_beginsamplescan(SampleScanState *node,
							Datum *params,
							int nparams,
							uint32 seed)
{
	SystemRowsSamplerData *sampler = (SystemRowsSamplerData *) node->tsm_state;
	int64		ntuples = DatumGetInt64(params[0]);

	if (ntuples < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TABLESAMPLE_ARGUMENT),
				 errmsg("sample size must not be negative")));

	sampler->seed = seed;
	sampler->ntuples = ntuples;
	sampler->lt = InvalidOffsetNumber;
	sampler->doneblocks = 0;
	/* lb will be initialized during first NextSampleBlock call */
	/* we intentionally do not change nblocks/firstblock/step here */

	/*
	 * We *must* use pagemode visibility checking in this module, so force
	 * that even though it's currently default.
	 */
	node->use_pagemode = true;
}