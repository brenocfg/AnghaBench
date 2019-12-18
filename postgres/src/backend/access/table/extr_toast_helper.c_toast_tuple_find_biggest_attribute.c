#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_12__ {TYPE_2__* ttc_attr; int /*<<< orphan*/ * ttc_values; TYPE_1__* ttc_rel; } ;
typedef  TYPE_4__ ToastTupleContext ;
struct TYPE_13__ {char attstorage; } ;
struct TYPE_11__ {int natts; } ;
struct TYPE_10__ {scalar_t__ tai_colflags; scalar_t__ tai_size; } ;
struct TYPE_9__ {TYPE_3__* rd_att; } ;
typedef  TYPE_5__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ MAXALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ TOASTCOL_IGNORE ; 
 scalar_t__ TOASTCOL_INCOMPRESSIBLE ; 
 int /*<<< orphan*/  TOAST_POINTER_SIZE ; 
 TYPE_5__* TupleDescAttr (TYPE_3__*,int) ; 
 scalar_t__ VARATT_IS_COMPRESSED (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 

int
toast_tuple_find_biggest_attribute(ToastTupleContext *ttc,
								   bool for_compression, bool check_main)
{
	TupleDesc	tupleDesc = ttc->ttc_rel->rd_att;
	int			numAttrs = tupleDesc->natts;
	int			biggest_attno = -1;
	int32		biggest_size = MAXALIGN(TOAST_POINTER_SIZE);
	int32		skip_colflags = TOASTCOL_IGNORE;
	int			i;

	if (for_compression)
		skip_colflags |= TOASTCOL_INCOMPRESSIBLE;

	for (i = 0; i < numAttrs; i++)
	{
		Form_pg_attribute att = TupleDescAttr(tupleDesc, i);

		if ((ttc->ttc_attr[i].tai_colflags & skip_colflags) != 0)
			continue;
		if (VARATT_IS_EXTERNAL(DatumGetPointer(ttc->ttc_values[i])))
			continue;			/* can't happen, toast_action would be 'p' */
		if (for_compression &&
			VARATT_IS_COMPRESSED(DatumGetPointer(ttc->ttc_values[i])))
			continue;
		if (check_main && att->attstorage != 'm')
			continue;
		if (!check_main && att->attstorage != 'x' && att->attstorage != 'e')
			continue;

		if (ttc->ttc_attr[i].tai_size > biggest_size)
		{
			biggest_attno = i;
			biggest_size = ttc->ttc_attr[i].tai_size;
		}
	}

	return biggest_attno;
}