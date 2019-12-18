#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int distance; int first; int second; int /*<<< orphan*/ * rfirst; int /*<<< orphan*/ * rsecond; } ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ FuzzyAttrMatchState ;

/* Variables and functions */
 scalar_t__ AttributeNumberIsValid (int) ; 
 void* InvalidAttrNumber ; 
 int MAX_FUZZY_DISTANCE ; 
 int strlen (char const*) ; 
 int varstr_levenshtein_less_equal (char const*,int,char const*,int,int,int,int,int,int) ; 

__attribute__((used)) static void
updateFuzzyAttrMatchState(int fuzzy_rte_penalty,
						  FuzzyAttrMatchState *fuzzystate, RangeTblEntry *rte,
						  const char *actual, const char *match, int attnum)
{
	int			columndistance;
	int			matchlen;

	/* Bail before computing the Levenshtein distance if there's no hope. */
	if (fuzzy_rte_penalty > fuzzystate->distance)
		return;

	/*
	 * Outright reject dropped columns, which can appear here with apparent
	 * empty actual names, per remarks within scanRTEForColumn().
	 */
	if (actual[0] == '\0')
		return;

	/* Use Levenshtein to compute match distance. */
	matchlen = strlen(match);
	columndistance =
		varstr_levenshtein_less_equal(actual, strlen(actual), match, matchlen,
									  1, 1, 1,
									  fuzzystate->distance + 1
									  - fuzzy_rte_penalty,
									  true);

	/*
	 * If more than half the characters are different, don't treat it as a
	 * match, to avoid making ridiculous suggestions.
	 */
	if (columndistance > matchlen / 2)
		return;

	/*
	 * From this point on, we can ignore the distinction between the RTE-name
	 * distance and the column-name distance.
	 */
	columndistance += fuzzy_rte_penalty;

	/*
	 * If the new distance is less than or equal to that of the best match
	 * found so far, update fuzzystate.
	 */
	if (columndistance < fuzzystate->distance)
	{
		/* Store new lowest observed distance for RTE */
		fuzzystate->distance = columndistance;
		fuzzystate->rfirst = rte;
		fuzzystate->first = attnum;
		fuzzystate->rsecond = NULL;
		fuzzystate->second = InvalidAttrNumber;
	}
	else if (columndistance == fuzzystate->distance)
	{
		/*
		 * This match distance may equal a prior match within this same range
		 * table.  When that happens, the prior match may also be given, but
		 * only if there is no more than two equally distant matches from the
		 * RTE (in turn, our caller will only accept two equally distant
		 * matches overall).
		 */
		if (AttributeNumberIsValid(fuzzystate->second))
		{
			/* Too many RTE-level matches */
			fuzzystate->rfirst = NULL;
			fuzzystate->first = InvalidAttrNumber;
			fuzzystate->rsecond = NULL;
			fuzzystate->second = InvalidAttrNumber;
			/* Clearly, distance is too low a bar (for *any* RTE) */
			fuzzystate->distance = columndistance - 1;
		}
		else if (AttributeNumberIsValid(fuzzystate->first))
		{
			/* Record as provisional second match for RTE */
			fuzzystate->rsecond = rte;
			fuzzystate->second = attnum;
		}
		else if (fuzzystate->distance <= MAX_FUZZY_DISTANCE)
		{
			/*
			 * Record as provisional first match (this can occasionally occur
			 * because previous lowest distance was "too low a bar", rather
			 * than being associated with a real match)
			 */
			fuzzystate->rfirst = rte;
			fuzzystate->first = attnum;
		}
	}
}