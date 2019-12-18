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
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ sp_syncing; } ;
struct TYPE_9__ {TYPE_2__* w_s; } ;
struct TYPE_7__ {int ga_len; } ;
struct TYPE_8__ {int /*<<< orphan*/ * b_syn_linecont_pat; int /*<<< orphan*/ * b_syn_linecont_prog; scalar_t__ b_syn_sync_linebreaks; scalar_t__ b_syn_sync_maxlines; scalar_t__ b_syn_sync_minlines; scalar_t__ b_syn_sync_flags; TYPE_1__ b_syn_patterns; } ;

/* Variables and functions */
 TYPE_5__* SYN_ITEMS (TYPE_2__*) ; 
 TYPE_4__* curwin ; 
 int /*<<< orphan*/  syn_remove_pattern (TYPE_2__*,int) ; 
 int /*<<< orphan*/  syn_stack_free_all (TYPE_2__*) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
syntax_sync_clear()
{
    int i;

    /* free the syntax patterns */
    for (i = curwin->w_s->b_syn_patterns.ga_len; --i >= 0; )
	if (SYN_ITEMS(curwin->w_s)[i].sp_syncing)
	    syn_remove_pattern(curwin->w_s, i);

    curwin->w_s->b_syn_sync_flags = 0;
    curwin->w_s->b_syn_sync_minlines = 0;
    curwin->w_s->b_syn_sync_maxlines = 0;
    curwin->w_s->b_syn_sync_linebreaks = 0;

    vim_regfree(curwin->w_s->b_syn_linecont_prog);
    curwin->w_s->b_syn_linecont_prog = NULL;
    vim_free(curwin->w_s->b_syn_linecont_pat);
    curwin->w_s->b_syn_linecont_pat = NULL;

    syn_stack_free_all(curwin->w_s);		/* Need to recompute all syntax. */
}