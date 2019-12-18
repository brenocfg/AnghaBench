#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int bits8 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_16__ {scalar_t__ attcacheoff; scalar_t__ attlen; int /*<<< orphan*/  attalign; } ;
struct TYPE_15__ {TYPE_2__* t_data; } ;
struct TYPE_14__ {int* t_bits; int t_hoff; } ;
struct TYPE_13__ {int natts; } ;
typedef  TYPE_2__* HeapTupleHeader ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ HeapTupleHasNulls (TYPE_3__*) ; 
 scalar_t__ HeapTupleHasVarWidth (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleNoNulls (TYPE_3__*) ; 
 TYPE_4__* TupleDescAttr (TYPE_1__*,int) ; 
 int att_addlength_pointer (int,int,char*) ; 
 int att_align_nominal (int,int /*<<< orphan*/ ) ; 
 int att_align_pointer (int,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ att_isnull (int,int*) ; 
 int /*<<< orphan*/  fetchatt (TYPE_4__*,char*) ; 

Datum
nocachegetattr(HeapTuple tuple,
			   int attnum,
			   TupleDesc tupleDesc)
{
	HeapTupleHeader tup = tuple->t_data;
	char	   *tp;				/* ptr to data part of tuple */
	bits8	   *bp = tup->t_bits;	/* ptr to null bitmap in tuple */
	bool		slow = false;	/* do we have to walk attrs? */
	int			off;			/* current offset within data */

	/* ----------------
	 *	 Three cases:
	 *
	 *	 1: No nulls and no variable-width attributes.
	 *	 2: Has a null or a var-width AFTER att.
	 *	 3: Has nulls or var-widths BEFORE att.
	 * ----------------
	 */

	attnum--;

	if (!HeapTupleNoNulls(tuple))
	{
		/*
		 * there's a null somewhere in the tuple
		 *
		 * check to see if any preceding bits are null...
		 */
		int			byte = attnum >> 3;
		int			finalbit = attnum & 0x07;

		/* check for nulls "before" final bit of last byte */
		if ((~bp[byte]) & ((1 << finalbit) - 1))
			slow = true;
		else
		{
			/* check for nulls in any "earlier" bytes */
			int			i;

			for (i = 0; i < byte; i++)
			{
				if (bp[i] != 0xFF)
				{
					slow = true;
					break;
				}
			}
		}
	}

	tp = (char *) tup + tup->t_hoff;

	if (!slow)
	{
		Form_pg_attribute att;

		/*
		 * If we get here, there are no nulls up to and including the target
		 * attribute.  If we have a cached offset, we can use it.
		 */
		att = TupleDescAttr(tupleDesc, attnum);
		if (att->attcacheoff >= 0)
			return fetchatt(att, tp + att->attcacheoff);

		/*
		 * Otherwise, check for non-fixed-length attrs up to and including
		 * target.  If there aren't any, it's safe to cheaply initialize the
		 * cached offsets for these attrs.
		 */
		if (HeapTupleHasVarWidth(tuple))
		{
			int			j;

			for (j = 0; j <= attnum; j++)
			{
				if (TupleDescAttr(tupleDesc, j)->attlen <= 0)
				{
					slow = true;
					break;
				}
			}
		}
	}

	if (!slow)
	{
		int			natts = tupleDesc->natts;
		int			j = 1;

		/*
		 * If we get here, we have a tuple with no nulls or var-widths up to
		 * and including the target attribute, so we can use the cached offset
		 * ... only we don't have it yet, or we'd not have got here.  Since
		 * it's cheap to compute offsets for fixed-width columns, we take the
		 * opportunity to initialize the cached offsets for *all* the leading
		 * fixed-width columns, in hope of avoiding future visits to this
		 * routine.
		 */
		TupleDescAttr(tupleDesc, 0)->attcacheoff = 0;

		/* we might have set some offsets in the slow path previously */
		while (j < natts && TupleDescAttr(tupleDesc, j)->attcacheoff > 0)
			j++;

		off = TupleDescAttr(tupleDesc, j - 1)->attcacheoff +
			TupleDescAttr(tupleDesc, j - 1)->attlen;

		for (; j < natts; j++)
		{
			Form_pg_attribute att = TupleDescAttr(tupleDesc, j);

			if (att->attlen <= 0)
				break;

			off = att_align_nominal(off, att->attalign);

			att->attcacheoff = off;

			off += att->attlen;
		}

		Assert(j > attnum);

		off = TupleDescAttr(tupleDesc, attnum)->attcacheoff;
	}
	else
	{
		bool		usecache = true;
		int			i;

		/*
		 * Now we know that we have to walk the tuple CAREFULLY.  But we still
		 * might be able to cache some offsets for next time.
		 *
		 * Note - This loop is a little tricky.  For each non-null attribute,
		 * we have to first account for alignment padding before the attr,
		 * then advance over the attr based on its length.  Nulls have no
		 * storage and no alignment padding either.  We can use/set
		 * attcacheoff until we reach either a null or a var-width attribute.
		 */
		off = 0;
		for (i = 0;; i++)		/* loop exit is at "break" */
		{
			Form_pg_attribute att = TupleDescAttr(tupleDesc, i);

			if (HeapTupleHasNulls(tuple) && att_isnull(i, bp))
			{
				usecache = false;
				continue;		/* this cannot be the target att */
			}

			/* If we know the next offset, we can skip the rest */
			if (usecache && att->attcacheoff >= 0)
				off = att->attcacheoff;
			else if (att->attlen == -1)
			{
				/*
				 * We can only cache the offset for a varlena attribute if the
				 * offset is already suitably aligned, so that there would be
				 * no pad bytes in any case: then the offset will be valid for
				 * either an aligned or unaligned value.
				 */
				if (usecache &&
					off == att_align_nominal(off, att->attalign))
					att->attcacheoff = off;
				else
				{
					off = att_align_pointer(off, att->attalign, -1,
											tp + off);
					usecache = false;
				}
			}
			else
			{
				/* not varlena, so safe to use att_align_nominal */
				off = att_align_nominal(off, att->attalign);

				if (usecache)
					att->attcacheoff = off;
			}

			if (i == attnum)
				break;

			off = att_addlength_pointer(off, att->attlen, tp + off);

			if (usecache && att->attlen <= 0)
				usecache = false;
		}
	}

	return fetchatt(TupleDescAttr(tupleDesc, attnum), tp + off);
}