#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ttc_flags; int /*<<< orphan*/  ttc_rel; TYPE_2__* ttc_attr; int /*<<< orphan*/ * ttc_values; } ;
typedef  TYPE_1__ ToastTupleContext ;
struct TYPE_5__ {int tai_colflags; int /*<<< orphan*/  tai_oldexternal; } ;
typedef  TYPE_2__ ToastAttrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int TOASTCOL_IGNORE ; 
 int TOASTCOL_NEEDS_FREE ; 
 int TOAST_NEEDS_CHANGE ; 
 int TOAST_NEEDS_FREE ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toast_save_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
toast_tuple_externalize(ToastTupleContext *ttc, int attribute, int options)
{
	Datum	   *value = &ttc->ttc_values[attribute];
	Datum		old_value = *value;
	ToastAttrInfo *attr = &ttc->ttc_attr[attribute];

	attr->tai_colflags |= TOASTCOL_IGNORE;
	*value = toast_save_datum(ttc->ttc_rel, old_value, attr->tai_oldexternal,
							  options);
	if ((attr->tai_colflags & TOASTCOL_NEEDS_FREE) != 0)
		pfree(DatumGetPointer(old_value));
	attr->tai_colflags |= TOASTCOL_NEEDS_FREE;
	ttc->ttc_flags |= (TOAST_NEEDS_CHANGE | TOAST_NEEDS_FREE);
}