#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int ttc_flags; int /*<<< orphan*/ * ttc_oldvalues; TYPE_5__* ttc_rel; TYPE_3__* ttc_attr; int /*<<< orphan*/ * ttc_values; } ;
typedef  TYPE_2__ ToastTupleContext ;
struct TYPE_8__ {int tai_colflags; } ;
typedef  TYPE_3__ ToastAttrInfo ;
struct TYPE_9__ {TYPE_1__* rd_att; } ;
struct TYPE_6__ {int natts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int TOASTCOL_NEEDS_DELETE_OLD ; 
 int TOASTCOL_NEEDS_FREE ; 
 int TOAST_NEEDS_DELETE_OLD ; 
 int TOAST_NEEDS_FREE ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toast_delete_datum (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void
toast_tuple_cleanup(ToastTupleContext *ttc)
{
	TupleDesc	tupleDesc = ttc->ttc_rel->rd_att;
	int			numAttrs = tupleDesc->natts;

	/*
	 * Free allocated temp values
	 */
	if ((ttc->ttc_flags & TOAST_NEEDS_FREE) != 0)
	{
		int			i;

		for (i = 0; i < numAttrs; i++)
		{
			ToastAttrInfo *attr = &ttc->ttc_attr[i];

			if ((attr->tai_colflags & TOASTCOL_NEEDS_FREE) != 0)
				pfree(DatumGetPointer(ttc->ttc_values[i]));
		}
	}

	/*
	 * Delete external values from the old tuple
	 */
	if ((ttc->ttc_flags & TOAST_NEEDS_DELETE_OLD) != 0)
	{
		int			i;

		for (i = 0; i < numAttrs; i++)
		{
			ToastAttrInfo *attr = &ttc->ttc_attr[i];

			if ((attr->tai_colflags & TOASTCOL_NEEDS_DELETE_OLD) != 0)
				toast_delete_datum(ttc->ttc_rel, ttc->ttc_oldvalues[i], false);
		}
	}
}