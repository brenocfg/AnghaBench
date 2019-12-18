#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int int32 ;
struct TYPE_10__ {int nentries; int nuserentries; int searchMode; int attnum; int curItemMatches; int recheckCurItem; int isFinished; int /*<<< orphan*/ * scanEntry; int /*<<< orphan*/ * additionalEntries; int /*<<< orphan*/ * requiredEntries; scalar_t__ nadditional; scalar_t__ nrequired; int /*<<< orphan*/  curItem; int /*<<< orphan*/  strategy; int /*<<< orphan*/ ** extra_data; int /*<<< orphan*/ * queryCategories; scalar_t__* queryValues; scalar_t__ query; int /*<<< orphan*/ * entryRes; } ;
struct TYPE_8__ {scalar_t__* canPartialMatch; } ;
struct TYPE_9__ {TYPE_1__ ginstate; int /*<<< orphan*/  nkeys; TYPE_3__* keys; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  int /*<<< orphan*/ * Pointer ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  GinTernaryValue ;
typedef  TYPE_1__ GinState ;
typedef  TYPE_2__* GinScanOpaque ;
typedef  TYPE_3__* GinScanKey ;
typedef  int /*<<< orphan*/  GinScanEntry ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GIN_CAT_EMPTY_ITEM ; 
 int /*<<< orphan*/  GIN_CAT_EMPTY_QUERY ; 
#define  GIN_SEARCH_MODE_ALL 130 
 int GIN_SEARCH_MODE_DEFAULT ; 
#define  GIN_SEARCH_MODE_EVERYTHING 129 
#define  GIN_SEARCH_MODE_INCLUDE_EMPTY 128 
 int /*<<< orphan*/  InvalidStrategy ; 
 int /*<<< orphan*/  ItemPointerSetMin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ginFillScanEntry (TYPE_2__*,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginInitConsistentFunction (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static void
ginFillScanKey(GinScanOpaque so, OffsetNumber attnum,
			   StrategyNumber strategy, int32 searchMode,
			   Datum query, uint32 nQueryValues,
			   Datum *queryValues, GinNullCategory *queryCategories,
			   bool *partial_matches, Pointer *extra_data)
{
	GinScanKey	key = &(so->keys[so->nkeys++]);
	GinState   *ginstate = &so->ginstate;
	uint32		nUserQueryValues = nQueryValues;
	uint32		i;

	/* Non-default search modes add one "hidden" entry to each key */
	if (searchMode != GIN_SEARCH_MODE_DEFAULT)
		nQueryValues++;
	key->nentries = nQueryValues;
	key->nuserentries = nUserQueryValues;

	key->scanEntry = (GinScanEntry *) palloc(sizeof(GinScanEntry) * nQueryValues);
	key->entryRes = (GinTernaryValue *) palloc0(sizeof(GinTernaryValue) * nQueryValues);

	key->query = query;
	key->queryValues = queryValues;
	key->queryCategories = queryCategories;
	key->extra_data = extra_data;
	key->strategy = strategy;
	key->searchMode = searchMode;
	key->attnum = attnum;

	ItemPointerSetMin(&key->curItem);
	key->curItemMatches = false;
	key->recheckCurItem = false;
	key->isFinished = false;
	key->nrequired = 0;
	key->nadditional = 0;
	key->requiredEntries = NULL;
	key->additionalEntries = NULL;

	ginInitConsistentFunction(ginstate, key);

	for (i = 0; i < nQueryValues; i++)
	{
		Datum		queryKey;
		GinNullCategory queryCategory;
		bool		isPartialMatch;
		Pointer		this_extra;

		if (i < nUserQueryValues)
		{
			/* set up normal entry using extractQueryFn's outputs */
			queryKey = queryValues[i];
			queryCategory = queryCategories[i];
			isPartialMatch =
				(ginstate->canPartialMatch[attnum - 1] && partial_matches)
				? partial_matches[i] : false;
			this_extra = (extra_data) ? extra_data[i] : NULL;
		}
		else
		{
			/* set up hidden entry */
			queryKey = (Datum) 0;
			switch (searchMode)
			{
				case GIN_SEARCH_MODE_INCLUDE_EMPTY:
					queryCategory = GIN_CAT_EMPTY_ITEM;
					break;
				case GIN_SEARCH_MODE_ALL:
					queryCategory = GIN_CAT_EMPTY_QUERY;
					break;
				case GIN_SEARCH_MODE_EVERYTHING:
					queryCategory = GIN_CAT_EMPTY_QUERY;
					break;
				default:
					elog(ERROR, "unexpected searchMode: %d", searchMode);
					queryCategory = 0;	/* keep compiler quiet */
					break;
			}
			isPartialMatch = false;
			this_extra = NULL;

			/*
			 * We set the strategy to a fixed value so that ginFillScanEntry
			 * can combine these entries for different scan keys.  This is
			 * safe because the strategy value in the entry struct is only
			 * used for partial-match cases.  It's OK to overwrite our local
			 * variable here because this is the last loop iteration.
			 */
			strategy = InvalidStrategy;
		}

		key->scanEntry[i] = ginFillScanEntry(so, attnum,
											 strategy, searchMode,
											 queryKey, queryCategory,
											 isPartialMatch, this_extra);
	}
}