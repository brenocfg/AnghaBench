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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  lt; int /*<<< orphan*/  seed; scalar_t__ cutoff; } ;
struct TYPE_4__ {int use_bulkread; int use_pagemode; scalar_t__ tsm_state; } ;
typedef  TYPE_1__ SampleScanState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_2__ BernoulliSamplerData ;

/* Variables and functions */
 double DatumGetFloat4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TABLESAMPLE_ARGUMENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 scalar_t__ PG_UINT32_MAX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ isnan (double) ; 
 double rint (double) ; 

__attribute__((used)) static void
bernoulli_beginsamplescan(SampleScanState *node,
						  Datum *params,
						  int nparams,
						  uint32 seed)
{
	BernoulliSamplerData *sampler = (BernoulliSamplerData *) node->tsm_state;
	double		percent = DatumGetFloat4(params[0]);
	double		dcutoff;

	if (percent < 0 || percent > 100 || isnan(percent))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TABLESAMPLE_ARGUMENT),
				 errmsg("sample percentage must be between 0 and 100")));

	/*
	 * The cutoff is sample probability times (PG_UINT32_MAX + 1); we have to
	 * store that as a uint64, of course.  Note that this gives strictly
	 * correct behavior at the limits of zero or one probability.
	 */
	dcutoff = rint(((double) PG_UINT32_MAX + 1) * percent / 100);
	sampler->cutoff = (uint64) dcutoff;
	sampler->seed = seed;
	sampler->lt = InvalidOffsetNumber;

	/*
	 * Use bulkread, since we're scanning all pages.  But pagemode visibility
	 * checking is a win only at larger sampling fractions.  The 25% cutoff
	 * here is based on very limited experimentation.
	 */
	node->use_bulkread = true;
	node->use_pagemode = (percent >= 25);
}