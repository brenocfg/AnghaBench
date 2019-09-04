#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ linenr_T ;
struct TYPE_8__ {scalar_t__ bh_data; } ;
typedef  TYPE_2__ bhdr_T ;
struct TYPE_7__ {scalar_t__ ml_line_count; scalar_t__ ml_locked_low; scalar_t__ ml_locked_high; int /*<<< orphan*/  ml_flags; int /*<<< orphan*/ * ml_mfp; } ;
struct TYPE_10__ {TYPE_1__ b_ml; } ;
struct TYPE_9__ {int* db_index; } ;
typedef  TYPE_3__ DATA_BL ;

/* Variables and functions */
 int DB_INDEX_MASK ; 
 int DB_MARKED ; 
 int /*<<< orphan*/  ML_FIND ; 
 int /*<<< orphan*/  ML_LOCKED_DIRTY ; 
 TYPE_5__* curbuf ; 
 scalar_t__ lowest_marked ; 
 TYPE_2__* ml_find_line (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 

linenr_T
ml_firstmarked()
{
    bhdr_T	*hp;
    DATA_BL	*dp;
    linenr_T	lnum;
    int		i;

    if (curbuf->b_ml.ml_mfp == NULL)
	return (linenr_T) 0;

    /*
     * The search starts with lowest_marked line. This is the last line where
     * a mark was found, adjusted by inserting/deleting lines.
     */
    for (lnum = lowest_marked; lnum <= curbuf->b_ml.ml_line_count; )
    {
	/*
	 * Find the data block containing the line.
	 * This also fills the stack with the blocks from the root to the data
	 * block This also releases any locked block.
	 */
	if ((hp = ml_find_line(curbuf, lnum, ML_FIND)) == NULL)
	    return (linenr_T)0;		    /* give error message? */

	dp = (DATA_BL *)(hp->bh_data);

	for (i = lnum - curbuf->b_ml.ml_locked_low;
			    lnum <= curbuf->b_ml.ml_locked_high; ++i, ++lnum)
	    if ((dp->db_index[i]) & DB_MARKED)
	    {
		(dp->db_index[i]) &= DB_INDEX_MASK;
		curbuf->b_ml.ml_flags |= ML_LOCKED_DIRTY;
		lowest_marked = lnum + 1;
		return lnum;
	    }
    }

    return (linenr_T) 0;
}