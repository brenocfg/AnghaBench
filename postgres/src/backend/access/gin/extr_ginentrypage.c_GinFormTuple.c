#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_19__ {int /*<<< orphan*/  index; int /*<<< orphan*/ * tupdesc; scalar_t__ oneCol; } ;
struct TYPE_18__ {int t_info; } ;
typedef  scalar_t__ Size ;
typedef  scalar_t__ Pointer ;
typedef  int OffsetNumber ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__ GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GIN_CAT_NORM_KEY ; 
 int GinCategoryOffset (TYPE_1__*,TYPE_2__*) ; 
 char* GinGetPosting (TYPE_1__*) ; 
 int GinMaxItemSize ; 
 int /*<<< orphan*/  GinSetNPosting (TYPE_1__*,int) ; 
 int /*<<< orphan*/  GinSetNullCategory (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinSetPostingOffset (TYPE_1__*,int) ; 
 int INDEX_SIZE_MASK ; 
 int IndexTupleHasNulls (TYPE_1__*) ; 
 int IndexTupleSize (TYPE_1__*) ; 
 int MAXALIGN (int) ; 
 int Max (int,int) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int SHORTALIGN (int) ; 
 int /*<<< orphan*/  UInt16GetDatum (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* index_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 TYPE_1__* repalloc (TYPE_1__*,int) ; 

IndexTuple
GinFormTuple(GinState *ginstate,
			 OffsetNumber attnum, Datum key, GinNullCategory category,
			 Pointer data, Size dataSize, int nipd,
			 bool errorTooBig)
{
	Datum		datums[2];
	bool		isnull[2];
	IndexTuple	itup;
	uint32		newsize;

	/* Build the basic tuple: optional column number, plus key datum */
	if (ginstate->oneCol)
	{
		datums[0] = key;
		isnull[0] = (category != GIN_CAT_NORM_KEY);
	}
	else
	{
		datums[0] = UInt16GetDatum(attnum);
		isnull[0] = false;
		datums[1] = key;
		isnull[1] = (category != GIN_CAT_NORM_KEY);
	}

	itup = index_form_tuple(ginstate->tupdesc[attnum - 1], datums, isnull);

	/*
	 * Determine and store offset to the posting list, making sure there is
	 * room for the category byte if needed.
	 *
	 * Note: because index_form_tuple MAXALIGNs the tuple size, there may well
	 * be some wasted pad space.  Is it worth recomputing the data length to
	 * prevent that?  That would also allow us to Assert that the real data
	 * doesn't overlap the GinNullCategory byte, which this code currently
	 * takes on faith.
	 */
	newsize = IndexTupleSize(itup);

	if (IndexTupleHasNulls(itup))
	{
		uint32		minsize;

		Assert(category != GIN_CAT_NORM_KEY);
		minsize = GinCategoryOffset(itup, ginstate) + sizeof(GinNullCategory);
		newsize = Max(newsize, minsize);
	}

	newsize = SHORTALIGN(newsize);

	GinSetPostingOffset(itup, newsize);
	GinSetNPosting(itup, nipd);

	/*
	 * Add space needed for posting list, if any.  Then check that the tuple
	 * won't be too big to store.
	 */
	newsize += dataSize;

	newsize = MAXALIGN(newsize);

	if (newsize > GinMaxItemSize)
	{
		if (errorTooBig)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("index row size %zu exceeds maximum %zu for index \"%s\"",
							(Size) newsize, (Size) GinMaxItemSize,
							RelationGetRelationName(ginstate->index))));
		pfree(itup);
		return NULL;
	}

	/*
	 * Resize tuple if needed
	 */
	if (newsize != IndexTupleSize(itup))
	{
		itup = repalloc(itup, newsize);

		/*
		 * PostgreSQL 9.3 and earlier did not clear this new space, so we
		 * might find uninitialized padding when reading tuples from disk.
		 */
		memset((char *) itup + IndexTupleSize(itup),
			   0, newsize - IndexTupleSize(itup));
		/* set new size in tuple header */
		itup->t_info &= ~INDEX_SIZE_MASK;
		itup->t_info |= newsize;
	}

	/*
	 * Copy in the posting list, if provided
	 */
	if (data)
	{
		char	   *ptr = GinGetPosting(itup);

		memcpy(ptr, data, dataSize);
	}

	/*
	 * Insert category byte, if needed
	 */
	if (category != GIN_CAT_NORM_KEY)
	{
		Assert(IndexTupleHasNulls(itup));
		GinSetNullCategory(itup, ginstate, category);
	}
	return itup;
}