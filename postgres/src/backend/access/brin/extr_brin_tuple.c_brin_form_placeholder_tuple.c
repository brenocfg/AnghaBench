#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int bits8 ;
struct TYPE_9__ {TYPE_1__* bd_tupdesc; } ;
struct TYPE_8__ {int bt_info; int /*<<< orphan*/  bt_blkno; } ;
struct TYPE_7__ {int natts; } ;
typedef  int Size ;
typedef  TYPE_2__ BrinTuple ;
typedef  TYPE_3__ BrinDesc ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 scalar_t__ BITMAPLEN (int) ; 
 int BRIN_NULLS_MASK ; 
 int BRIN_PLACEHOLDER_MASK ; 
 int HIGHBIT ; 
 int MAXALIGN (int) ; 
 int SizeOfBrinTuple ; 
 TYPE_2__* palloc0 (int) ; 

BrinTuple *
brin_form_placeholder_tuple(BrinDesc *brdesc, BlockNumber blkno, Size *size)
{
	Size		len;
	Size		hoff;
	BrinTuple  *rettuple;
	int			keyno;
	bits8	   *bitP;
	int			bitmask;

	/* compute total space needed: always add nulls */
	len = SizeOfBrinTuple;
	len += BITMAPLEN(brdesc->bd_tupdesc->natts * 2);
	len = hoff = MAXALIGN(len);

	rettuple = palloc0(len);
	rettuple->bt_blkno = blkno;
	rettuple->bt_info = hoff;
	rettuple->bt_info |= BRIN_NULLS_MASK | BRIN_PLACEHOLDER_MASK;

	bitP = ((bits8 *) ((char *) rettuple + SizeOfBrinTuple)) - 1;
	bitmask = HIGHBIT;
	/* set allnulls true for all attributes */
	for (keyno = 0; keyno < brdesc->bd_tupdesc->natts; keyno++)
	{
		if (bitmask != HIGHBIT)
			bitmask <<= 1;
		else
		{
			bitP += 1;
			*bitP = 0x0;
			bitmask = 1;
		}

		*bitP |= bitmask;
	}
	/* no need to set hasnulls */

	*size = len;
	return rettuple;
}