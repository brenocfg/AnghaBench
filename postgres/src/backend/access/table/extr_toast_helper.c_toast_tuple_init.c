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
struct varlena {int dummy; } ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_12__ {int ttc_flags; TYPE_2__* ttc_attr; int /*<<< orphan*/ * ttc_values; scalar_t__* ttc_isnull; int /*<<< orphan*/ * ttc_oldisnull; int /*<<< orphan*/ * ttc_oldvalues; TYPE_1__* ttc_rel; } ;
typedef  TYPE_4__ ToastTupleContext ;
struct TYPE_13__ {int attlen; char attstorage; } ;
struct TYPE_11__ {int natts; } ;
struct TYPE_10__ {int /*<<< orphan*/  tai_colflags; int /*<<< orphan*/  tai_size; struct varlena* tai_oldexternal; } ;
struct TYPE_9__ {TYPE_3__* rd_att; } ;
typedef  TYPE_5__* Form_pg_attribute ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (struct varlena*) ; 
 int /*<<< orphan*/  TOASTCOL_IGNORE ; 
 int /*<<< orphan*/  TOASTCOL_NEEDS_DELETE_OLD ; 
 int /*<<< orphan*/  TOASTCOL_NEEDS_FREE ; 
 int TOAST_HAS_NULLS ; 
 int TOAST_NEEDS_CHANGE ; 
 int TOAST_NEEDS_DELETE_OLD ; 
 int TOAST_NEEDS_FREE ; 
 TYPE_5__* TupleDescAttr (TYPE_3__*,int) ; 
 scalar_t__ VARATT_IS_EXTERNAL (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_ONDISK (struct varlena*) ; 
 int /*<<< orphan*/  VARSIZE_ANY (struct varlena*) ; 
 int /*<<< orphan*/  VARSIZE_EXTERNAL (struct varlena*) ; 
 struct varlena* detoast_attr (struct varlena*) ; 
 struct varlena* detoast_external_attr (struct varlena*) ; 
 scalar_t__ memcmp (char*,char*,int /*<<< orphan*/ ) ; 

void
toast_tuple_init(ToastTupleContext *ttc)
{
	TupleDesc	tupleDesc = ttc->ttc_rel->rd_att;
	int			numAttrs = tupleDesc->natts;
	int			i;

	ttc->ttc_flags = 0;

	for (i = 0; i < numAttrs; i++)
	{
		Form_pg_attribute att = TupleDescAttr(tupleDesc, i);
		struct varlena *old_value;
		struct varlena *new_value;

		ttc->ttc_attr[i].tai_colflags = 0;
		ttc->ttc_attr[i].tai_oldexternal = NULL;

		if (ttc->ttc_oldvalues != NULL)
		{
			/*
			 * For UPDATE get the old and new values of this attribute
			 */
			old_value =
				(struct varlena *) DatumGetPointer(ttc->ttc_oldvalues[i]);
			new_value =
				(struct varlena *) DatumGetPointer(ttc->ttc_values[i]);

			/*
			 * If the old value is stored on disk, check if it has changed so
			 * we have to delete it later.
			 */
			if (att->attlen == -1 && !ttc->ttc_oldisnull[i] &&
				VARATT_IS_EXTERNAL_ONDISK(old_value))
			{
				if (ttc->ttc_isnull[i] ||
					!VARATT_IS_EXTERNAL_ONDISK(new_value) ||
					memcmp((char *) old_value, (char *) new_value,
						   VARSIZE_EXTERNAL(old_value)) != 0)
				{
					/*
					 * The old external stored value isn't needed any more
					 * after the update
					 */
					ttc->ttc_attr[i].tai_colflags |= TOASTCOL_NEEDS_DELETE_OLD;
					ttc->ttc_flags |= TOAST_NEEDS_DELETE_OLD;
				}
				else
				{
					/*
					 * This attribute isn't changed by this update so we reuse
					 * the original reference to the old value in the new
					 * tuple.
					 */
					ttc->ttc_attr[i].tai_colflags |= TOASTCOL_IGNORE;
					continue;
				}
			}
		}
		else
		{
			/*
			 * For INSERT simply get the new value
			 */
			new_value = (struct varlena *) DatumGetPointer(ttc->ttc_values[i]);
		}

		/*
		 * Handle NULL attributes
		 */
		if (ttc->ttc_isnull[i])
		{
			ttc->ttc_attr[i].tai_colflags |= TOASTCOL_IGNORE;
			ttc->ttc_flags |= TOAST_HAS_NULLS;
			continue;
		}

		/*
		 * Now look at varlena attributes
		 */
		if (att->attlen == -1)
		{
			/*
			 * If the table's attribute says PLAIN always, force it so.
			 */
			if (att->attstorage == 'p')
				ttc->ttc_attr[i].tai_colflags |= TOASTCOL_IGNORE;

			/*
			 * We took care of UPDATE above, so any external value we find
			 * still in the tuple must be someone else's that we cannot reuse
			 * (this includes the case of an out-of-line in-memory datum).
			 * Fetch it back (without decompression, unless we are forcing
			 * PLAIN storage).  If necessary, we'll push it out as a new
			 * external value below.
			 */
			if (VARATT_IS_EXTERNAL(new_value))
			{
				ttc->ttc_attr[i].tai_oldexternal = new_value;
				if (att->attstorage == 'p')
					new_value = detoast_attr(new_value);
				else
					new_value = detoast_external_attr(new_value);
				ttc->ttc_values[i] = PointerGetDatum(new_value);
				ttc->ttc_attr[i].tai_colflags |= TOASTCOL_NEEDS_FREE;
				ttc->ttc_flags |= (TOAST_NEEDS_CHANGE | TOAST_NEEDS_FREE);
			}

			/*
			 * Remember the size of this attribute
			 */
			ttc->ttc_attr[i].tai_size = VARSIZE_ANY(new_value);
		}
		else
		{
			/*
			 * Not a varlena attribute, plain storage always
			 */
			ttc->ttc_attr[i].tai_colflags |= TOASTCOL_IGNORE;
		}
	}
}