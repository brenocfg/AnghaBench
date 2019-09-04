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
struct TYPE_8__ {scalar_t__ sst_lnum; scalar_t__ sst_tick; struct TYPE_8__* sst_next; } ;
typedef  TYPE_2__ synstate_T ;
typedef  scalar_t__ disptick_T ;
struct TYPE_7__ {scalar_t__ ml_line_count; } ;
struct TYPE_10__ {TYPE_1__ b_ml; } ;
struct TYPE_9__ {scalar_t__ b_sst_len; scalar_t__ b_sst_lasttick; TYPE_2__* b_sst_first; int /*<<< orphan*/ * b_sst_array; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ Rows ; 
 int TRUE ; 
 TYPE_3__* syn_block ; 
 TYPE_5__* syn_buf ; 
 int /*<<< orphan*/  syn_stack_free_entry (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int
syn_stack_cleanup()
{
    synstate_T	*p, *prev;
    disptick_T	tick;
    int		above;
    int		dist;
    int		retval = FALSE;

    if (syn_block->b_sst_array == NULL || syn_block->b_sst_first == NULL)
	return retval;

    /* Compute normal distance between non-displayed entries. */
    if (syn_block->b_sst_len <= Rows)
	dist = 999999;
    else
	dist = syn_buf->b_ml.ml_line_count / (syn_block->b_sst_len - Rows) + 1;

    /*
     * Go through the list to find the "tick" for the oldest entry that can
     * be removed.  Set "above" when the "tick" for the oldest entry is above
     * "b_sst_lasttick" (the display tick wraps around).
     */
    tick = syn_block->b_sst_lasttick;
    above = FALSE;
    prev = syn_block->b_sst_first;
    for (p = prev->sst_next; p != NULL; prev = p, p = p->sst_next)
    {
	if (prev->sst_lnum + dist > p->sst_lnum)
	{
	    if (p->sst_tick > syn_block->b_sst_lasttick)
	    {
		if (!above || p->sst_tick < tick)
		    tick = p->sst_tick;
		above = TRUE;
	    }
	    else if (!above && p->sst_tick < tick)
		tick = p->sst_tick;
	}
    }

    /*
     * Go through the list to make the entries for the oldest tick at an
     * interval of several lines.
     */
    prev = syn_block->b_sst_first;
    for (p = prev->sst_next; p != NULL; prev = p, p = p->sst_next)
    {
	if (p->sst_tick == tick && prev->sst_lnum + dist > p->sst_lnum)
	{
	    /* Move this entry from used list to free list */
	    prev->sst_next = p->sst_next;
	    syn_stack_free_entry(syn_block, p);
	    p = prev;
	    retval = TRUE;
	}
    }
    return retval;
}