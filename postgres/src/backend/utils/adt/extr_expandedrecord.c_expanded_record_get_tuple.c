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
struct TYPE_3__ {int flags; int /*<<< orphan*/  dnulls; int /*<<< orphan*/  dvalues; int /*<<< orphan*/  er_tupdesc; int /*<<< orphan*/ * fvalue; } ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__ ExpandedRecordHeader ;

/* Variables and functions */
 int ER_FLAG_DVALUES_VALID ; 
 int ER_FLAG_FVALUE_VALID ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HeapTuple
expanded_record_get_tuple(ExpandedRecordHeader *erh)
{
	/* Easy case if we still have original tuple */
	if (erh->flags & ER_FLAG_FVALUE_VALID)
		return erh->fvalue;

	/* Else just build a tuple from datums */
	if (erh->flags & ER_FLAG_DVALUES_VALID)
		return heap_form_tuple(erh->er_tupdesc, erh->dvalues, erh->dnulls);

	/* Expanded record is empty */
	return NULL;
}