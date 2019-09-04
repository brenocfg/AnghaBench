#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int lnum; } ;
struct TYPE_8__ {TYPE_6__ uh_cursor; TYPE_3__* uh_entry; } ;
typedef  TYPE_2__ u_header_T ;
struct TYPE_9__ {scalar_t__ ue_top; scalar_t__ ue_bot; int ue_size; int /*<<< orphan*/ * ue_array; } ;
typedef  TYPE_3__ u_entry_T ;
typedef  int linenr_T ;
struct TYPE_7__ {int ml_line_count; } ;
struct TYPE_10__ {TYPE_1__ b_ml; int /*<<< orphan*/ * b_u_curhead; TYPE_2__* b_u_newhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ STRCMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearpos (TYPE_6__*) ; 
 TYPE_4__* curbuf ; 
 int /*<<< orphan*/  ml_get_buf (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

void
u_find_first_changed()
{
    u_header_T	*uhp = curbuf->b_u_newhead;
    u_entry_T   *uep;
    linenr_T	lnum;

    if (curbuf->b_u_curhead != NULL || uhp == NULL)
	return;  /* undid something in an autocmd? */

    /* Check that the last undo block was for the whole file. */
    uep = uhp->uh_entry;
    if (uep->ue_top != 0 || uep->ue_bot != 0)
	return;

    for (lnum = 1; lnum < curbuf->b_ml.ml_line_count
					      && lnum <= uep->ue_size; ++lnum)
	if (STRCMP(ml_get_buf(curbuf, lnum, FALSE),
						uep->ue_array[lnum - 1]) != 0)
	{
	    clearpos(&(uhp->uh_cursor));
	    uhp->uh_cursor.lnum = lnum;
	    return;
	}
    if (curbuf->b_ml.ml_line_count != uep->ue_size)
    {
	/* lines added or deleted at the end, put the cursor there */
	clearpos(&(uhp->uh_cursor));
	uhp->uh_cursor.lnum = lnum;
    }
}