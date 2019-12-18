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
struct TYPE_14__ {int flags; int nfields; int* dnulls; char* fstartptr; char* fendptr; TYPE_1__ hdr; int /*<<< orphan*/  er_domaininfo; int /*<<< orphan*/  er_decltypeid; int /*<<< orphan*/ * dvalues; scalar_t__ flat_size; TYPE_2__* er_tupdesc; } ;
struct TYPE_13__ {int attlen; int /*<<< orphan*/  attbyval; scalar_t__ attisdropped; } ;
struct TYPE_12__ {int natts; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int ER_FLAG_DVALUES_ALLOCED ; 
 int ER_FLAG_DVALUES_VALID ; 
 int ER_FLAG_FVALUE_VALID ; 
 int ER_FLAG_HAVE_EXTERNAL ; 
 int ER_FLAG_IS_DOMAIN ; 
 int ER_FLAG_IS_DUMMY ; 
 int /*<<< orphan*/  ExpandedRecordGetRODatum (TYPE_4__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_2__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL (scalar_t__) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  deconstruct_expanded_record (TYPE_4__*) ; 
 int /*<<< orphan*/  detoast_external_attr (struct varlena*) ; 
 int /*<<< orphan*/  domain_check (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_short_term_cxt (TYPE_4__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ unlikely (int) ; 

void
expanded_record_set_fields(ExpandedRecordHeader *erh,
						   const Datum *newValues, const bool *isnulls,
						   bool expand_external)
{
	TupleDesc	tupdesc;
	Datum	   *dvalues;
	bool	   *dnulls;
	int			fnumber;
	MemoryContext oldcxt;

	/* Shouldn't ever be trying to assign new data to a dummy header */
	Assert(!(erh->flags & ER_FLAG_IS_DUMMY));

	/* If we haven't yet deconstructed the tuple, do that */
	if (!(erh->flags & ER_FLAG_DVALUES_VALID))
		deconstruct_expanded_record(erh);

	/* Tuple descriptor must be valid by now */
	tupdesc = erh->er_tupdesc;
	Assert(erh->nfields == tupdesc->natts);

	/* Flattened value will no longer represent record accurately */
	erh->flags &= ~ER_FLAG_FVALUE_VALID;
	/* And we don't know the flattened size either */
	erh->flat_size = 0;

	oldcxt = MemoryContextSwitchTo(erh->hdr.eoh_context);

	dvalues = erh->dvalues;
	dnulls = erh->dnulls;

	for (fnumber = 0; fnumber < erh->nfields; fnumber++)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, fnumber);
		Datum		newValue;
		bool		isnull;

		/* Ignore dropped columns */
		if (attr->attisdropped)
			continue;

		newValue = newValues[fnumber];
		isnull = isnulls[fnumber];

		if (!attr->attbyval)
		{
			/*
			 * Copy new field value into record's context, and deal with
			 * detoasting, if needed.
			 */
			if (!isnull)
			{
				/* Is it an external toasted value? */
				if (attr->attlen == -1 &&
					VARATT_IS_EXTERNAL(DatumGetPointer(newValue)))
				{
					if (expand_external)
					{
						/* Detoast as requested while copying the value */
						newValue = PointerGetDatum(detoast_external_attr((struct varlena *) DatumGetPointer(newValue)));
					}
					else
					{
						/* Just copy the value */
						newValue = datumCopy(newValue, false, -1);
						/* If it's still external, remember that */
						if (VARATT_IS_EXTERNAL(DatumGetPointer(newValue)))
							erh->flags |= ER_FLAG_HAVE_EXTERNAL;
					}
				}
				else
				{
					/* Not an external value, just copy it */
					newValue = datumCopy(newValue, false, attr->attlen);
				}

				/* Remember that we have field(s) that need to be pfree'd */
				erh->flags |= ER_FLAG_DVALUES_ALLOCED;
			}

			/*
			 * Free old field value, if any (not likely, since really we ought
			 * to be inserting into an empty record).
			 */
			if (unlikely(!dnulls[fnumber]))
			{
				char	   *oldValue;

				oldValue = (char *) DatumGetPointer(dvalues[fnumber]);
				/* Don't try to pfree a part of the original flat record */
				if (oldValue < erh->fstartptr || oldValue >= erh->fendptr)
					pfree(oldValue);
			}
		}

		/* And finally we can insert the new field. */
		dvalues[fnumber] = newValue;
		dnulls[fnumber] = isnull;
	}

	/*
	 * Because we don't guarantee atomicity of set_fields(), we can just leave
	 * checking of domain constraints to occur as the final step; if it throws
	 * an error, too bad.
	 */
	if (erh->flags & ER_FLAG_IS_DOMAIN)
	{
		/* We run domain_check in a short-lived context to limit cruft */
		MemoryContextSwitchTo(get_short_term_cxt(erh));

		domain_check(ExpandedRecordGetRODatum(erh), false,
					 erh->er_decltypeid,
					 &erh->er_domaininfo,
					 erh->hdr.eoh_context);
	}

	MemoryContextSwitchTo(oldcxt);
}