#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nfields; int* dnulls; int /*<<< orphan*/ * fvalue; int /*<<< orphan*/ * dvalues; } ;
typedef  TYPE_1__ ExpandedRecordHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ ExpandedRecordIsEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  deconstruct_expanded_record (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_getsysattr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ unlikely (int) ; 

Datum
expanded_record_fetch_field(ExpandedRecordHeader *erh, int fnumber,
							bool *isnull)
{
	if (fnumber > 0)
	{
		/* Empty record has null fields */
		if (ExpandedRecordIsEmpty(erh))
		{
			*isnull = true;
			return (Datum) 0;
		}
		/* Make sure we have deconstructed form */
		deconstruct_expanded_record(erh);
		/* Out-of-range field number reads as null */
		if (unlikely(fnumber > erh->nfields))
		{
			*isnull = true;
			return (Datum) 0;
		}
		*isnull = erh->dnulls[fnumber - 1];
		return erh->dvalues[fnumber - 1];
	}
	else
	{
		/* System columns read as null if we haven't got flat tuple */
		if (erh->fvalue == NULL)
		{
			*isnull = true;
			return (Datum) 0;
		}
		/* heap_getsysattr doesn't actually use tupdesc, so just pass null */
		return heap_getsysattr(erh->fvalue, fnumber, NULL, isnull);
	}
}