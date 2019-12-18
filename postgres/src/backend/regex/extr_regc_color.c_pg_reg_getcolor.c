#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct colormap {int numcmranges; int hiarraycols; int /*<<< orphan*/ * hicolormap; TYPE_1__* cmranges; } ;
struct TYPE_2__ {scalar_t__ cmin; scalar_t__ cmax; int rownum; } ;
typedef  TYPE_1__ colormaprange ;
typedef  int /*<<< orphan*/  color ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 scalar_t__ MAX_SIMPLE_CHR ; 
 int /*<<< orphan*/  assert (int) ; 
 int cclass_column_index (struct colormap*,scalar_t__) ; 

color
pg_reg_getcolor(struct colormap *cm, chr c)
{
	int			rownum,
				colnum,
				low,
				high;

	/* Should not be used for chrs in the locolormap */
	assert(c > MAX_SIMPLE_CHR);

	/*
	 * Find which row it's in.  The colormapranges are in order, so we can use
	 * binary search.
	 */
	rownum = 0;					/* if no match, use array row zero */
	low = 0;
	high = cm->numcmranges;
	while (low < high)
	{
		int			middle = low + (high - low) / 2;
		const colormaprange *cmr = &cm->cmranges[middle];

		if (c < cmr->cmin)
			high = middle;
		else if (c > cmr->cmax)
			low = middle + 1;
		else
		{
			rownum = cmr->rownum;	/* found a match */
			break;
		}
	}

	/*
	 * Find which column it's in --- this is all locale-dependent.
	 */
	if (cm->hiarraycols > 1)
	{
		colnum = cclass_column_index(cm, c);
		return cm->hicolormap[rownum * cm->hiarraycols + colnum];
	}
	else
	{
		/* fast path if no relevant cclasses */
		return cm->hicolormap[rownum];
	}
}