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
struct TYPE_4__ {int ttc_flags; TYPE_2__* ttc_attr; int /*<<< orphan*/ * ttc_values; } ;
typedef  TYPE_1__ ToastTupleContext ;
struct TYPE_5__ {int tai_colflags; int /*<<< orphan*/  tai_size; } ;
typedef  TYPE_2__ ToastAttrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetPointer (int /*<<< orphan*/ ) ; 
 int TOASTCOL_INCOMPRESSIBLE ; 
 int TOASTCOL_NEEDS_FREE ; 
 int TOAST_NEEDS_CHANGE ; 
 int TOAST_NEEDS_FREE ; 
 int /*<<< orphan*/  VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toast_compress_datum (int /*<<< orphan*/ ) ; 

void
toast_tuple_try_compression(ToastTupleContext *ttc, int attribute)
{
	Datum	   *value = &ttc->ttc_values[attribute];
	Datum		new_value = toast_compress_datum(*value);
	ToastAttrInfo *attr = &ttc->ttc_attr[attribute];

	if (DatumGetPointer(new_value) != NULL)
	{
		/* successful compression */
		if ((attr->tai_colflags & TOASTCOL_NEEDS_FREE) != 0)
			pfree(DatumGetPointer(*value));
		*value = new_value;
		attr->tai_colflags |= TOASTCOL_NEEDS_FREE;
		attr->tai_size = VARSIZE(DatumGetPointer(*value));
		ttc->ttc_flags |= (TOAST_NEEDS_CHANGE | TOAST_NEEDS_FREE);
	}
	else
	{
		/* incompressible, ignore on subsequent compression passes */
		attr->tai_colflags |= TOASTCOL_INCOMPRESSIBLE;
	}
}