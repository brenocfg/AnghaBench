#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_17__ {int /*<<< orphan*/  eoh_context; } ;
struct TYPE_19__ {int flags; char* fstartptr; char* fendptr; int nfields; int /*<<< orphan*/ * dvalues; int /*<<< orphan*/ * dnulls; int /*<<< orphan*/  er_tupdesc; scalar_t__ flat_size; TYPE_2__* fvalue; int /*<<< orphan*/  er_short_term_cxt; TYPE_1__ hdr; } ;
struct TYPE_18__ {int t_len; scalar_t__ t_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  attbyval; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__ ExpandedRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int ER_FLAGS_NON_DATA ; 
 int ER_FLAG_DVALUES_ALLOCED ; 
 int ER_FLAG_FVALUE_ALLOCED ; 
 int ER_FLAG_FVALUE_VALID ; 
 int ER_FLAG_HAVE_EXTERNAL ; 
 int ER_FLAG_IS_DOMAIN ; 
 int ER_FLAG_IS_DUMMY ; 
 scalar_t__ HeapTupleHasExternal (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_14__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_domain_for_new_tuple (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  get_short_term_cxt (TYPE_3__*) ; 
 TYPE_2__* heap_copytuple (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 TYPE_2__* toast_flatten_tuple (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
expanded_record_set_tuple(ExpandedRecordHeader *erh,
						  HeapTuple tuple,
						  bool copy,
						  bool expand_external)
{
	int			oldflags;
	HeapTuple	oldtuple;
	char	   *oldfstartptr;
	char	   *oldfendptr;
	int			newflags;
	HeapTuple	newtuple;
	MemoryContext oldcxt;

	/* Shouldn't ever be trying to assign new data to a dummy header */
	Assert(!(erh->flags & ER_FLAG_IS_DUMMY));

	/*
	 * Before performing the assignment, see if result will satisfy domain.
	 */
	if (erh->flags & ER_FLAG_IS_DOMAIN)
		check_domain_for_new_tuple(erh, tuple);

	/*
	 * If we need to get rid of out-of-line field values, do so, using the
	 * short-term context to avoid leaking whatever cruft the toast fetch
	 * might generate.
	 */
	if (expand_external && tuple)
	{
		/* Assert caller didn't ask for unsupported case */
		Assert(copy);
		if (HeapTupleHasExternal(tuple))
		{
			oldcxt = MemoryContextSwitchTo(get_short_term_cxt(erh));
			tuple = toast_flatten_tuple(tuple, erh->er_tupdesc);
			MemoryContextSwitchTo(oldcxt);
		}
		else
			expand_external = false;	/* need not clean up below */
	}

	/*
	 * Initialize new flags, keeping only non-data status bits.
	 */
	oldflags = erh->flags;
	newflags = oldflags & ER_FLAGS_NON_DATA;

	/*
	 * Copy tuple into local storage if needed.  We must be sure this succeeds
	 * before we start to modify the expanded record's state.
	 */
	if (copy && tuple)
	{
		oldcxt = MemoryContextSwitchTo(erh->hdr.eoh_context);
		newtuple = heap_copytuple(tuple);
		newflags |= ER_FLAG_FVALUE_ALLOCED;
		MemoryContextSwitchTo(oldcxt);

		/* We can now flush anything that detoasting might have leaked. */
		if (expand_external)
			MemoryContextReset(erh->er_short_term_cxt);
	}
	else
		newtuple = tuple;

	/* Make copies of fields we're about to overwrite */
	oldtuple = erh->fvalue;
	oldfstartptr = erh->fstartptr;
	oldfendptr = erh->fendptr;

	/*
	 * It's now safe to update the expanded record's state.
	 */
	if (newtuple)
	{
		/* Save flat representation */
		erh->fvalue = newtuple;
		erh->fstartptr = (char *) newtuple->t_data;
		erh->fendptr = ((char *) newtuple->t_data) + newtuple->t_len;
		newflags |= ER_FLAG_FVALUE_VALID;

		/* Remember if we have any out-of-line field values */
		if (HeapTupleHasExternal(newtuple))
			newflags |= ER_FLAG_HAVE_EXTERNAL;
	}
	else
	{
		erh->fvalue = NULL;
		erh->fstartptr = erh->fendptr = NULL;
	}

	erh->flags = newflags;

	/* Reset flat-size info; we don't bother to make it valid now */
	erh->flat_size = 0;

	/*
	 * Now, release any storage belonging to old field values.  It's safe to
	 * do this because ER_FLAG_DVALUES_VALID is no longer set in erh->flags;
	 * even if we fail partway through, the record is valid, and at worst
	 * we've failed to reclaim some space.
	 */
	if (oldflags & ER_FLAG_DVALUES_ALLOCED)
	{
		TupleDesc	tupdesc = erh->er_tupdesc;
		int			i;

		for (i = 0; i < erh->nfields; i++)
		{
			if (!erh->dnulls[i] &&
				!(TupleDescAttr(tupdesc, i)->attbyval))
			{
				char	   *oldValue = (char *) DatumGetPointer(erh->dvalues[i]);

				if (oldValue < oldfstartptr || oldValue >= oldfendptr)
					pfree(oldValue);
			}
		}
	}

	/* Likewise free the old tuple, if it was locally allocated */
	if (oldflags & ER_FLAG_FVALUE_ALLOCED)
		heap_freetuple(oldtuple);

	/* We won't make a new deconstructed representation until/unless needed */
}