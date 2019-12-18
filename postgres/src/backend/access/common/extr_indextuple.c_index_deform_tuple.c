#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bits8 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_12__ {int attcacheoff; int attlen; int /*<<< orphan*/  attalign; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_info; } ;
struct TYPE_10__ {int natts; } ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  TYPE_2__* IndexTuple ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int INDEX_MAX_KEYS ; 
 int IndexInfoFindDataOffset (int /*<<< orphan*/ ) ; 
 int IndexTupleHasNulls (TYPE_2__*) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int att_addlength_pointer (int,int,char*) ; 
 int att_align_nominal (int,int /*<<< orphan*/ ) ; 
 int att_align_pointer (int,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ att_isnull (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetchatt (TYPE_3__*,char*) ; 

void
index_deform_tuple(IndexTuple tup, TupleDesc tupleDescriptor,
				   Datum *values, bool *isnull)
{
	int			hasnulls = IndexTupleHasNulls(tup);
	int			natts = tupleDescriptor->natts; /* number of atts to extract */
	int			attnum;
	char	   *tp;				/* ptr to tuple data */
	int			off;			/* offset in tuple data */
	bits8	   *bp;				/* ptr to null bitmap in tuple */
	bool		slow = false;	/* can we use/set attcacheoff? */

	/* Assert to protect callers who allocate fixed-size arrays */
	Assert(natts <= INDEX_MAX_KEYS);

	/* XXX "knows" t_bits are just after fixed tuple header! */
	bp = (bits8 *) ((char *) tup + sizeof(IndexTupleData));

	tp = (char *) tup + IndexInfoFindDataOffset(tup->t_info);
	off = 0;

	for (attnum = 0; attnum < natts; attnum++)
	{
		Form_pg_attribute thisatt = TupleDescAttr(tupleDescriptor, attnum);

		if (hasnulls && att_isnull(attnum, bp))
		{
			values[attnum] = (Datum) 0;
			isnull[attnum] = true;
			slow = true;		/* can't use attcacheoff anymore */
			continue;
		}

		isnull[attnum] = false;

		if (!slow && thisatt->attcacheoff >= 0)
			off = thisatt->attcacheoff;
		else if (thisatt->attlen == -1)
		{
			/*
			 * We can only cache the offset for a varlena attribute if the
			 * offset is already suitably aligned, so that there would be no
			 * pad bytes in any case: then the offset will be valid for either
			 * an aligned or unaligned value.
			 */
			if (!slow &&
				off == att_align_nominal(off, thisatt->attalign))
				thisatt->attcacheoff = off;
			else
			{
				off = att_align_pointer(off, thisatt->attalign, -1,
										tp + off);
				slow = true;
			}
		}
		else
		{
			/* not varlena, so safe to use att_align_nominal */
			off = att_align_nominal(off, thisatt->attalign);

			if (!slow)
				thisatt->attcacheoff = off;
		}

		values[attnum] = fetchatt(thisatt, tp + off);

		off = att_addlength_pointer(off, thisatt->attlen, tp + off);

		if (thisatt->attlen <= 0)
			slow = true;		/* can't use attcacheoff anymore */
	}
}