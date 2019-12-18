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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_19__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_18__ {int natts; } ;
typedef  TYPE_2__* IndexTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* CopyIndexTuple (TYPE_2__*) ; 
 int INDEX_MAX_KEYS ; 
 scalar_t__ IndexTupleSize (TYPE_2__*) ; 
 int /*<<< orphan*/  TupleDescCopy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TupleDescSize (TYPE_1__*) ; 
 int /*<<< orphan*/  index_deform_tuple (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* index_form_tuple (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

IndexTuple
index_truncate_tuple(TupleDesc sourceDescriptor, IndexTuple source,
					 int leavenatts)
{
	TupleDesc	truncdesc;
	Datum		values[INDEX_MAX_KEYS];
	bool		isnull[INDEX_MAX_KEYS];
	IndexTuple	truncated;

	Assert(leavenatts <= sourceDescriptor->natts);

	/* Easy case: no truncation actually required */
	if (leavenatts == sourceDescriptor->natts)
		return CopyIndexTuple(source);

	/* Create temporary descriptor to scribble on */
	truncdesc = palloc(TupleDescSize(sourceDescriptor));
	TupleDescCopy(truncdesc, sourceDescriptor);
	truncdesc->natts = leavenatts;

	/* Deform, form copy of tuple with fewer attributes */
	index_deform_tuple(source, truncdesc, values, isnull);
	truncated = index_form_tuple(truncdesc, values, isnull);
	truncated->t_tid = source->t_tid;
	Assert(IndexTupleSize(truncated) <= IndexTupleSize(source));

	/*
	 * Cannot leak memory here, TupleDescCopy() doesn't allocate any inner
	 * structure, so, plain pfree() should clean all allocated memory
	 */
	pfree(truncdesc);

	return truncated;
}