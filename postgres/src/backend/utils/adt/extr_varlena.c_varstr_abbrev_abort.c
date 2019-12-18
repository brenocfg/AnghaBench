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
struct TYPE_4__ {double prop_card; int /*<<< orphan*/  full_card; int /*<<< orphan*/  abbr_card; } ;
typedef  TYPE_1__ VarStringSortSupport ;
struct TYPE_5__ {int /*<<< orphan*/  abbreviate; scalar_t__ ssup_extra; } ;
typedef  TYPE_2__* SortSupport ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,double,double,double,...) ; 
 double estimateHyperLogLog (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_sort ; 

__attribute__((used)) static bool
varstr_abbrev_abort(int memtupcount, SortSupport ssup)
{
	VarStringSortSupport *sss = (VarStringSortSupport *) ssup->ssup_extra;
	double		abbrev_distinct,
				key_distinct;

	Assert(ssup->abbreviate);

	/* Have a little patience */
	if (memtupcount < 100)
		return false;

	abbrev_distinct = estimateHyperLogLog(&sss->abbr_card);
	key_distinct = estimateHyperLogLog(&sss->full_card);

	/*
	 * Clamp cardinality estimates to at least one distinct value.  While
	 * NULLs are generally disregarded, if only NULL values were seen so far,
	 * that might misrepresent costs if we failed to clamp.
	 */
	if (abbrev_distinct <= 1.0)
		abbrev_distinct = 1.0;

	if (key_distinct <= 1.0)
		key_distinct = 1.0;

	/*
	 * In the worst case all abbreviated keys are identical, while at the same
	 * time there are differences within full key strings not captured in
	 * abbreviations.
	 */
#ifdef TRACE_SORT
	if (trace_sort)
	{
		double		norm_abbrev_card = abbrev_distinct / (double) memtupcount;

		elog(LOG, "varstr_abbrev: abbrev_distinct after %d: %f "
			 "(key_distinct: %f, norm_abbrev_card: %f, prop_card: %f)",
			 memtupcount, abbrev_distinct, key_distinct, norm_abbrev_card,
			 sss->prop_card);
	}
#endif

	/*
	 * If the number of distinct abbreviated keys approximately matches the
	 * number of distinct authoritative original keys, that's reason enough to
	 * proceed.  We can win even with a very low cardinality set if most
	 * tie-breakers only memcmp().  This is by far the most important
	 * consideration.
	 *
	 * While comparisons that are resolved at the abbreviated key level are
	 * considerably cheaper than tie-breakers resolved with memcmp(), both of
	 * those two outcomes are so much cheaper than a full strcoll() once
	 * sorting is underway that it doesn't seem worth it to weigh abbreviated
	 * cardinality against the overall size of the set in order to more
	 * accurately model costs.  Assume that an abbreviated comparison, and an
	 * abbreviated comparison with a cheap memcmp()-based authoritative
	 * resolution are equivalent.
	 */
	if (abbrev_distinct > key_distinct * sss->prop_card)
	{
		/*
		 * When we have exceeded 10,000 tuples, decay required cardinality
		 * aggressively for next call.
		 *
		 * This is useful because the number of comparisons required on
		 * average increases at a linearithmic rate, and at roughly 10,000
		 * tuples that factor will start to dominate over the linear costs of
		 * string transformation (this is a conservative estimate).  The decay
		 * rate is chosen to be a little less aggressive than halving -- which
		 * (since we're called at points at which memtupcount has doubled)
		 * would never see the cost model actually abort past the first call
		 * following a decay.  This decay rate is mostly a precaution against
		 * a sudden, violent swing in how well abbreviated cardinality tracks
		 * full key cardinality.  The decay also serves to prevent a marginal
		 * case from being aborted too late, when too much has already been
		 * invested in string transformation.
		 *
		 * It's possible for sets of several million distinct strings with
		 * mere tens of thousands of distinct abbreviated keys to still
		 * benefit very significantly.  This will generally occur provided
		 * each abbreviated key is a proxy for a roughly uniform number of the
		 * set's full keys. If it isn't so, we hope to catch that early and
		 * abort.  If it isn't caught early, by the time the problem is
		 * apparent it's probably not worth aborting.
		 */
		if (memtupcount > 10000)
			sss->prop_card *= 0.65;

		return false;
	}

	/*
	 * Abort abbreviation strategy.
	 *
	 * The worst case, where all abbreviated keys are identical while all
	 * original strings differ will typically only see a regression of about
	 * 10% in execution time for small to medium sized lists of strings.
	 * Whereas on modern CPUs where cache stalls are the dominant cost, we can
	 * often expect very large improvements, particularly with sets of strings
	 * of moderately high to high abbreviated cardinality.  There is little to
	 * lose but much to gain, which our strategy reflects.
	 */
#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG, "varstr_abbrev: aborted abbreviation at %d "
			 "(abbrev_distinct: %f, key_distinct: %f, prop_card: %f)",
			 memtupcount, abbrev_distinct, key_distinct, sss->prop_card);
#endif

	return true;
}