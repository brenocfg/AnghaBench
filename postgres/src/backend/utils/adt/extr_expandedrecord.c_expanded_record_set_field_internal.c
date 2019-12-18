#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_11__ {int /*<<< orphan*/  eoh_context; } ;
struct TYPE_14__ {int flags; scalar_t__ nfields; int* dnulls; char* fstartptr; char* fendptr; scalar_t__ flat_size; int /*<<< orphan*/ * dvalues; int /*<<< orphan*/  er_short_term_cxt; TYPE_1__ hdr; TYPE_2__* er_tupdesc; } ;
struct TYPE_13__ {int attlen; int /*<<< orphan*/  attbyval; } ;
struct TYPE_12__ {scalar_t__ natts; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int ER_FLAG_DVALUES_ALLOCED ; 
 int ER_FLAG_DVALUES_VALID ; 
 int ER_FLAG_FVALUE_VALID ; 
 int ER_FLAG_HAVE_EXTERNAL ; 
 int ER_FLAG_IS_DOMAIN ; 
 int ER_FLAG_IS_DUMMY ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_2__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  check_domain_for_new_field (TYPE_4__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  deconstruct_expanded_record (TYPE_4__*) ; 
 int /*<<< orphan*/  detoast_external_attr (struct varlena*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_short_term_cxt (TYPE_4__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ unlikely (int) ; 

void
expanded_record_set_field_internal(ExpandedRecordHeader *erh, int fnumber,
								   Datum newValue, bool isnull,
								   bool expand_external,
								   bool check_constraints)
{
	TupleDesc	tupdesc;
	Form_pg_attribute attr;
	Datum	   *dvalues;
	bool	   *dnulls;
	char	   *oldValue;

	/*
	 * Shouldn't ever be trying to assign new data to a dummy header, except
	 * in the case of an internal call for field inlining.
	 */
	Assert(!(erh->flags & ER_FLAG_IS_DUMMY) || !check_constraints);

	/* Before performing the assignment, see if result will satisfy domain */
	if ((erh->flags & ER_FLAG_IS_DOMAIN) && check_constraints)
		check_domain_for_new_field(erh, fnumber, newValue, isnull);

	/* If we haven't yet deconstructed the tuple, do that */
	if (!(erh->flags & ER_FLAG_DVALUES_VALID))
		deconstruct_expanded_record(erh);

	/* Tuple descriptor must be valid by now */
	tupdesc = erh->er_tupdesc;
	Assert(erh->nfields == tupdesc->natts);

	/* Caller error if fnumber is system column or nonexistent column */
	if (unlikely(fnumber <= 0 || fnumber > erh->nfields))
		elog(ERROR, "cannot assign to field %d of expanded record", fnumber);

	/*
	 * Copy new field value into record's context, and deal with detoasting,
	 * if needed.
	 */
	attr = TupleDescAttr(tupdesc, fnumber - 1);
	if (!isnull && !attr->attbyval)
	{
		MemoryContext oldcxt;

		/* If requested, detoast any external value */
		if (expand_external)
		{
			if (attr->attlen == -1 &&
				VARATT_IS_EXTERNAL(DatumGetPointer(newValue)))
			{
				/* Detoasting should be done in short-lived context. */
				oldcxt = MemoryContextSwitchTo(get_short_term_cxt(erh));
				newValue = PointerGetDatum(detoast_external_attr((struct varlena *) DatumGetPointer(newValue)));
				MemoryContextSwitchTo(oldcxt);
			}
			else
				expand_external = false;	/* need not clean up below */
		}

		/* Copy value into record's context */
		oldcxt = MemoryContextSwitchTo(erh->hdr.eoh_context);
		newValue = datumCopy(newValue, false, attr->attlen);
		MemoryContextSwitchTo(oldcxt);

		/* We can now flush anything that detoasting might have leaked */
		if (expand_external)
			MemoryContextReset(erh->er_short_term_cxt);

		/* Remember that we have field(s) that may need to be pfree'd */
		erh->flags |= ER_FLAG_DVALUES_ALLOCED;

		/*
		 * While we're here, note whether it's an external toasted value,
		 * because that could mean we need to inline it later.  (Think not to
		 * merge this into the previous expand_external logic: datumCopy could
		 * by itself have made the value non-external.)
		 */
		if (attr->attlen == -1 &&
			VARATT_IS_EXTERNAL(DatumGetPointer(newValue)))
			erh->flags |= ER_FLAG_HAVE_EXTERNAL;
	}

	/*
	 * We're ready to make irreversible changes.
	 */
	dvalues = erh->dvalues;
	dnulls = erh->dnulls;

	/* Flattened value will no longer represent record accurately */
	erh->flags &= ~ER_FLAG_FVALUE_VALID;
	/* And we don't know the flattened size either */
	erh->flat_size = 0;

	/* Grab old field value for pfree'ing, if needed. */
	if (!attr->attbyval && !dnulls[fnumber - 1])
		oldValue = (char *) DatumGetPointer(dvalues[fnumber - 1]);
	else
		oldValue = NULL;

	/* And finally we can insert the new field. */
	dvalues[fnumber - 1] = newValue;
	dnulls[fnumber - 1] = isnull;

	/*
	 * Free old field if needed; this keeps repeated field replacements from
	 * bloating the record's storage.  If the pfree somehow fails, it won't
	 * corrupt the record.
	 *
	 * If we're updating a dummy header, we can't risk pfree'ing the old
	 * value, because most likely the expanded record's main header still has
	 * a pointer to it.  This won't result in any sustained memory leak, since
	 * whatever we just allocated here is in the short-lived domain check
	 * context.
	 */
	if (oldValue && !(erh->flags & ER_FLAG_IS_DUMMY))
	{
		/* Don't try to pfree a part of the original flat record */
		if (oldValue < erh->fstartptr || oldValue >= erh->fendptr)
			pfree(oldValue);
	}
}