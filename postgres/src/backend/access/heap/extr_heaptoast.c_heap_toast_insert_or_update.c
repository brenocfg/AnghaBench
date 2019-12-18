#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_23__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_30__ {int* ttc_isnull; int* ttc_oldisnull; int ttc_flags; TYPE_4__* ttc_attr; int /*<<< orphan*/ * ttc_oldvalues; int /*<<< orphan*/ * ttc_values; TYPE_5__* ttc_rel; } ;
typedef  TYPE_3__ ToastTupleContext ;
struct TYPE_31__ {scalar_t__ tai_size; int /*<<< orphan*/  tai_colflags; } ;
typedef  TYPE_4__ ToastAttrInfo ;
struct TYPE_34__ {int t_len; TYPE_6__* t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; } ;
struct TYPE_33__ {int t_hoff; int /*<<< orphan*/ * t_bits; int /*<<< orphan*/  t_infomask; } ;
struct TYPE_32__ {TYPE_1__* rd_rel; TYPE_2__* rd_att; } ;
struct TYPE_29__ {int natts; } ;
struct TYPE_28__ {char attstorage; } ;
struct TYPE_27__ {scalar_t__ relkind; scalar_t__ reltoastrelid; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_5__* Relation ;
typedef  TYPE_6__* HeapTupleHeader ;
typedef  TYPE_7__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BITMAPLEN (int) ; 
 int HEAPTUPLESIZE ; 
 int HEAP_INSERT_SPECULATIVE ; 
 int /*<<< orphan*/  HeapTupleHeaderSetNatts (TYPE_6__*,int) ; 
 scalar_t__ InvalidOid ; 
 void* MAXALIGN (int) ; 
 int MaxHeapAttributeNumber ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RelationGetToastTupleTarget (TYPE_5__*,int /*<<< orphan*/ ) ; 
 void* SizeofHeapTupleHeader ; 
 int /*<<< orphan*/  TOASTCOL_INCOMPRESSIBLE ; 
 int TOAST_HAS_NULLS ; 
 int TOAST_NEEDS_CHANGE ; 
 int /*<<< orphan*/  TOAST_TUPLE_TARGET ; 
 scalar_t__ TOAST_TUPLE_TARGET_MAIN ; 
 TYPE_23__* TupleDescAttr (TYPE_2__*,int) ; 
 scalar_t__ heap_compute_data_size (TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_7__*,TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_fill_tuple (TYPE_2__*,int /*<<< orphan*/ *,int*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,TYPE_6__*,void*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  toast_tuple_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  toast_tuple_externalize (TYPE_3__*,int,int) ; 
 int toast_tuple_find_biggest_attribute (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  toast_tuple_init (TYPE_3__*) ; 
 int /*<<< orphan*/  toast_tuple_try_compression (TYPE_3__*,int) ; 

HeapTuple
heap_toast_insert_or_update(Relation rel, HeapTuple newtup, HeapTuple oldtup,
							int options)
{
	HeapTuple	result_tuple;
	TupleDesc	tupleDesc;
	int			numAttrs;

	Size		maxDataLen;
	Size		hoff;

	bool		toast_isnull[MaxHeapAttributeNumber];
	bool		toast_oldisnull[MaxHeapAttributeNumber];
	Datum		toast_values[MaxHeapAttributeNumber];
	Datum		toast_oldvalues[MaxHeapAttributeNumber];
	ToastAttrInfo toast_attr[MaxHeapAttributeNumber];
	ToastTupleContext ttc;

	/*
	 * Ignore the INSERT_SPECULATIVE option. Speculative insertions/super
	 * deletions just normally insert/delete the toast values. It seems
	 * easiest to deal with that here, instead on, potentially, multiple
	 * callers.
	 */
	options &= ~HEAP_INSERT_SPECULATIVE;

	/*
	 * We should only ever be called for tuples of plain relations or
	 * materialized views --- recursing on a toast rel is bad news.
	 */
	Assert(rel->rd_rel->relkind == RELKIND_RELATION ||
		   rel->rd_rel->relkind == RELKIND_MATVIEW);

	/*
	 * Get the tuple descriptor and break down the tuple(s) into fields.
	 */
	tupleDesc = rel->rd_att;
	numAttrs = tupleDesc->natts;

	Assert(numAttrs <= MaxHeapAttributeNumber);
	heap_deform_tuple(newtup, tupleDesc, toast_values, toast_isnull);
	if (oldtup != NULL)
		heap_deform_tuple(oldtup, tupleDesc, toast_oldvalues, toast_oldisnull);

	/* ----------
	 * Prepare for toasting
	 * ----------
	 */
	ttc.ttc_rel = rel;
	ttc.ttc_values = toast_values;
	ttc.ttc_isnull = toast_isnull;
	if (oldtup == NULL)
	{
		ttc.ttc_oldvalues = NULL;
		ttc.ttc_oldisnull = NULL;
	}
	else
	{
		ttc.ttc_oldvalues = toast_oldvalues;
		ttc.ttc_oldisnull = toast_oldisnull;
	}
	ttc.ttc_attr = toast_attr;
	toast_tuple_init(&ttc);

	/* ----------
	 * Compress and/or save external until data fits into target length
	 *
	 *	1: Inline compress attributes with attstorage 'x', and store very
	 *	   large attributes with attstorage 'x' or 'e' external immediately
	 *	2: Store attributes with attstorage 'x' or 'e' external
	 *	3: Inline compress attributes with attstorage 'm'
	 *	4: Store attributes with attstorage 'm' external
	 * ----------
	 */

	/* compute header overhead --- this should match heap_form_tuple() */
	hoff = SizeofHeapTupleHeader;
	if ((ttc.ttc_flags & TOAST_HAS_NULLS) != 0)
		hoff += BITMAPLEN(numAttrs);
	hoff = MAXALIGN(hoff);
	/* now convert to a limit on the tuple data size */
	maxDataLen = RelationGetToastTupleTarget(rel, TOAST_TUPLE_TARGET) - hoff;

	/*
	 * Look for attributes with attstorage 'x' to compress.  Also find large
	 * attributes with attstorage 'x' or 'e', and store them external.
	 */
	while (heap_compute_data_size(tupleDesc,
								  toast_values, toast_isnull) > maxDataLen)
	{
		int			biggest_attno;

		biggest_attno = toast_tuple_find_biggest_attribute(&ttc, true, false);
		if (biggest_attno < 0)
			break;

		/*
		 * Attempt to compress it inline, if it has attstorage 'x'
		 */
		if (TupleDescAttr(tupleDesc, biggest_attno)->attstorage == 'x')
			toast_tuple_try_compression(&ttc, biggest_attno);
		else
		{
			/* has attstorage 'e', ignore on subsequent compression passes */
			toast_attr[biggest_attno].tai_colflags |= TOASTCOL_INCOMPRESSIBLE;
		}

		/*
		 * If this value is by itself more than maxDataLen (after compression
		 * if any), push it out to the toast table immediately, if possible.
		 * This avoids uselessly compressing other fields in the common case
		 * where we have one long field and several short ones.
		 *
		 * XXX maybe the threshold should be less than maxDataLen?
		 */
		if (toast_attr[biggest_attno].tai_size > maxDataLen &&
			rel->rd_rel->reltoastrelid != InvalidOid)
			toast_tuple_externalize(&ttc, biggest_attno, options);
	}

	/*
	 * Second we look for attributes of attstorage 'x' or 'e' that are still
	 * inline, and make them external.  But skip this if there's no toast
	 * table to push them to.
	 */
	while (heap_compute_data_size(tupleDesc,
								  toast_values, toast_isnull) > maxDataLen &&
		   rel->rd_rel->reltoastrelid != InvalidOid)
	{
		int			biggest_attno;

		biggest_attno = toast_tuple_find_biggest_attribute(&ttc, false, false);
		if (biggest_attno < 0)
			break;
		toast_tuple_externalize(&ttc, biggest_attno, options);
	}

	/*
	 * Round 3 - this time we take attributes with storage 'm' into
	 * compression
	 */
	while (heap_compute_data_size(tupleDesc,
								  toast_values, toast_isnull) > maxDataLen)
	{
		int			biggest_attno;

		biggest_attno = toast_tuple_find_biggest_attribute(&ttc, true, true);
		if (biggest_attno < 0)
			break;

		toast_tuple_try_compression(&ttc, biggest_attno);
	}

	/*
	 * Finally we store attributes of type 'm' externally.  At this point we
	 * increase the target tuple size, so that 'm' attributes aren't stored
	 * externally unless really necessary.
	 */
	maxDataLen = TOAST_TUPLE_TARGET_MAIN - hoff;

	while (heap_compute_data_size(tupleDesc,
								  toast_values, toast_isnull) > maxDataLen &&
		   rel->rd_rel->reltoastrelid != InvalidOid)
	{
		int			biggest_attno;

		biggest_attno = toast_tuple_find_biggest_attribute(&ttc, false, true);
		if (biggest_attno < 0)
			break;

		toast_tuple_externalize(&ttc, biggest_attno, options);
	}

	/*
	 * In the case we toasted any values, we need to build a new heap tuple
	 * with the changed values.
	 */
	if ((ttc.ttc_flags & TOAST_NEEDS_CHANGE) != 0)
	{
		HeapTupleHeader olddata = newtup->t_data;
		HeapTupleHeader new_data;
		int32		new_header_len;
		int32		new_data_len;
		int32		new_tuple_len;

		/*
		 * Calculate the new size of the tuple.
		 *
		 * Note: we used to assume here that the old tuple's t_hoff must equal
		 * the new_header_len value, but that was incorrect.  The old tuple
		 * might have a smaller-than-current natts, if there's been an ALTER
		 * TABLE ADD COLUMN since it was stored; and that would lead to a
		 * different conclusion about the size of the null bitmap, or even
		 * whether there needs to be one at all.
		 */
		new_header_len = SizeofHeapTupleHeader;
		if ((ttc.ttc_flags & TOAST_HAS_NULLS) != 0)
			new_header_len += BITMAPLEN(numAttrs);
		new_header_len = MAXALIGN(new_header_len);
		new_data_len = heap_compute_data_size(tupleDesc,
											  toast_values, toast_isnull);
		new_tuple_len = new_header_len + new_data_len;

		/*
		 * Allocate and zero the space needed, and fill HeapTupleData fields.
		 */
		result_tuple = (HeapTuple) palloc0(HEAPTUPLESIZE + new_tuple_len);
		result_tuple->t_len = new_tuple_len;
		result_tuple->t_self = newtup->t_self;
		result_tuple->t_tableOid = newtup->t_tableOid;
		new_data = (HeapTupleHeader) ((char *) result_tuple + HEAPTUPLESIZE);
		result_tuple->t_data = new_data;

		/*
		 * Copy the existing tuple header, but adjust natts and t_hoff.
		 */
		memcpy(new_data, olddata, SizeofHeapTupleHeader);
		HeapTupleHeaderSetNatts(new_data, numAttrs);
		new_data->t_hoff = new_header_len;

		/* Copy over the data, and fill the null bitmap if needed */
		heap_fill_tuple(tupleDesc,
						toast_values,
						toast_isnull,
						(char *) new_data + new_header_len,
						new_data_len,
						&(new_data->t_infomask),
						((ttc.ttc_flags & TOAST_HAS_NULLS) != 0) ?
						new_data->t_bits : NULL);
	}
	else
		result_tuple = newtup;

	toast_tuple_cleanup(&ttc);

	return result_tuple;
}