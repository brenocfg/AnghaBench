#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_12__ {int /*<<< orphan*/ * arg; int /*<<< orphan*/  func; } ;
struct TYPE_9__ {int /*<<< orphan*/  eoh_context; } ;
struct TYPE_11__ {int /*<<< orphan*/  er_tupdesc_id; TYPE_2__* er_tupdesc; TYPE_7__ er_mcb; TYPE_1__ hdr; int /*<<< orphan*/  er_typmod; int /*<<< orphan*/  er_typeid; } ;
struct TYPE_10__ {scalar_t__ tdrefcount; int /*<<< orphan*/  tdtypmod; int /*<<< orphan*/  tdtypeid; } ;
typedef  TYPE_3__ ExpandedRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  DecrTupleDescRefCount (TYPE_2__*) ; 
 int /*<<< orphan*/  ER_mc_callback ; 
 int /*<<< orphan*/  MemoryContextRegisterResetCallback (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  assign_record_type_identifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TupleDesc
expanded_record_fetch_tupdesc(ExpandedRecordHeader *erh)
{
	TupleDesc	tupdesc;

	/* Easy if we already have it (but caller should have checked already) */
	if (erh->er_tupdesc)
		return erh->er_tupdesc;

	/* Lookup the composite type's tupdesc using the typcache */
	tupdesc = lookup_rowtype_tupdesc(erh->er_typeid, erh->er_typmod);

	/*
	 * If it's a refcounted tupdesc rather than a statically allocated one, we
	 * want to manage the refcount with a memory context callback rather than
	 * assuming that the CurrentResourceOwner is longer-lived than this
	 * expanded object.
	 */
	if (tupdesc->tdrefcount >= 0)
	{
		/* Register callback if we didn't already */
		if (erh->er_mcb.arg == NULL)
		{
			erh->er_mcb.func = ER_mc_callback;
			erh->er_mcb.arg = (void *) erh;
			MemoryContextRegisterResetCallback(erh->hdr.eoh_context,
											   &erh->er_mcb);
		}

		/* Remember our own pointer */
		erh->er_tupdesc = tupdesc;
		tupdesc->tdrefcount++;

		/* Release the pin lookup_rowtype_tupdesc acquired */
		DecrTupleDescRefCount(tupdesc);
	}
	else
	{
		/* Just remember the pointer */
		erh->er_tupdesc = tupdesc;
	}

	/* In either case, fetch the process-global ID for this tupdesc */
	erh->er_tupdesc_id = assign_record_type_identifier(tupdesc->tdtypeid,
													   tupdesc->tdtypmod);

	return tupdesc;
}