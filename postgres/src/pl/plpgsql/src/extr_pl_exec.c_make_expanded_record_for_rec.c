#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TupleDesc ;
struct TYPE_14__ {scalar_t__ er_decltypeid; } ;
struct TYPE_13__ {scalar_t__ rectypeid; } ;
typedef  TYPE_1__ PLpgSQL_rec ;
typedef  int /*<<< orphan*/  PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ ExpandedRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  ExpandedRecordIsDomain (TYPE_2__*) ; 
 scalar_t__ RECORDOID ; 
 scalar_t__ expanded_record_get_tupdesc (TYPE_2__*) ; 
 int /*<<< orphan*/  get_eval_mcontext (int /*<<< orphan*/ *) ; 
 TYPE_2__* make_expanded_record_from_exprecord (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* make_expanded_record_from_tupdesc (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* make_expanded_record_from_typeid (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_rectypeid (TYPE_1__*) ; 

__attribute__((used)) static ExpandedRecordHeader *
make_expanded_record_for_rec(PLpgSQL_execstate *estate,
							 PLpgSQL_rec *rec,
							 TupleDesc srctupdesc,
							 ExpandedRecordHeader *srcerh)
{
	ExpandedRecordHeader *newerh;
	MemoryContext mcontext = get_eval_mcontext(estate);

	if (rec->rectypeid != RECORDOID)
	{
		/*
		 * Make sure rec->rectypeid is up-to-date before using it.
		 */
		revalidate_rectypeid(rec);

		/*
		 * New record must be of desired type, but maybe srcerh has already
		 * done all the same lookups.
		 */
		if (srcerh && rec->rectypeid == srcerh->er_decltypeid)
			newerh = make_expanded_record_from_exprecord(srcerh,
														 mcontext);
		else
			newerh = make_expanded_record_from_typeid(rec->rectypeid, -1,
													  mcontext);
	}
	else
	{
		/*
		 * We'll adopt the input tupdesc.  We can still use
		 * make_expanded_record_from_exprecord, if srcerh isn't a composite
		 * domain.  (If it is, we effectively adopt its base type.)
		 */
		if (srcerh && !ExpandedRecordIsDomain(srcerh))
			newerh = make_expanded_record_from_exprecord(srcerh,
														 mcontext);
		else
		{
			if (!srctupdesc)
				srctupdesc = expanded_record_get_tupdesc(srcerh);
			newerh = make_expanded_record_from_tupdesc(srctupdesc,
													   mcontext);
		}
	}

	return newerh;
}