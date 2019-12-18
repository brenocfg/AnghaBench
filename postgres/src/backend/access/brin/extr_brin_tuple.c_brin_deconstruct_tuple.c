#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bits8 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {TYPE_2__** bd_info; TYPE_1__* bd_tupdesc; } ;
struct TYPE_11__ {int attlen; int /*<<< orphan*/  attalign; } ;
struct TYPE_10__ {int oi_nstored; } ;
struct TYPE_9__ {int natts; } ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ BrinDesc ;

/* Variables and functions */
 TYPE_3__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 long att_addlength_pointer (long,int,char*) ; 
 long att_align_nominal (long,int /*<<< orphan*/ ) ; 
 long att_align_pointer (long,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  att_isnull (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brtuple_disk_tupdesc (TYPE_4__*) ; 
 int /*<<< orphan*/  fetchatt (TYPE_3__*,char*) ; 

__attribute__((used)) static inline void
brin_deconstruct_tuple(BrinDesc *brdesc,
					   char *tp, bits8 *nullbits, bool nulls,
					   Datum *values, bool *allnulls, bool *hasnulls)
{
	int			attnum;
	int			stored;
	TupleDesc	diskdsc;
	long		off;

	/*
	 * First iterate to natts to obtain both null flags for each attribute.
	 * Note that we reverse the sense of the att_isnull test, because we store
	 * 1 for a null value (rather than a 1 for a not null value as is the
	 * att_isnull convention used elsewhere.)  See brin_form_tuple.
	 */
	for (attnum = 0; attnum < brdesc->bd_tupdesc->natts; attnum++)
	{
		/*
		 * the "all nulls" bit means that all values in the page range for
		 * this column are nulls.  Therefore there are no values in the tuple
		 * data area.
		 */
		allnulls[attnum] = nulls && !att_isnull(attnum, nullbits);

		/*
		 * the "has nulls" bit means that some tuples have nulls, but others
		 * have not-null values.  Therefore we know the tuple contains data
		 * for this column.
		 *
		 * The hasnulls bits follow the allnulls bits in the same bitmask.
		 */
		hasnulls[attnum] =
			nulls && !att_isnull(brdesc->bd_tupdesc->natts + attnum, nullbits);
	}

	/*
	 * Iterate to obtain each attribute's stored values.  Note that since we
	 * may reuse attribute entries for more than one column, we cannot cache
	 * offsets here.
	 */
	diskdsc = brtuple_disk_tupdesc(brdesc);
	stored = 0;
	off = 0;
	for (attnum = 0; attnum < brdesc->bd_tupdesc->natts; attnum++)
	{
		int			datumno;

		if (allnulls[attnum])
		{
			stored += brdesc->bd_info[attnum]->oi_nstored;
			continue;
		}

		for (datumno = 0;
			 datumno < brdesc->bd_info[attnum]->oi_nstored;
			 datumno++)
		{
			Form_pg_attribute thisatt = TupleDescAttr(diskdsc, stored);

			if (thisatt->attlen == -1)
			{
				off = att_align_pointer(off, thisatt->attalign, -1,
										tp + off);
			}
			else
			{
				/* not varlena, so safe to use att_align_nominal */
				off = att_align_nominal(off, thisatt->attalign);
			}

			values[stored++] = fetchatt(thisatt, tp + off);

			off = att_addlength_pointer(off, thisatt->attlen, tp + off);
		}
	}
}