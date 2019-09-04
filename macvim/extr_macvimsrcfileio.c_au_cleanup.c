#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ event_T ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  reg_prog; int /*<<< orphan*/ * pat; struct TYPE_5__* cmd; struct TYPE_5__* cmds; } ;
typedef  TYPE_1__ AutoPat ;
typedef  TYPE_1__ AutoCmd ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ NUM_EVENTS ; 
 scalar_t__ au_need_clean ; 
 scalar_t__ autocmd_busy ; 
 TYPE_1__** first_autopat ; 
 int /*<<< orphan*/  vim_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vim_regfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
au_cleanup()
{
    AutoPat	*ap, **prev_ap;
    AutoCmd	*ac, **prev_ac;
    event_T	event;

    if (autocmd_busy || !au_need_clean)
	return;

    /* loop over all events */
    for (event = (event_T)0; (int)event < (int)NUM_EVENTS;
					    event = (event_T)((int)event + 1))
    {
	/* loop over all autocommand patterns */
	prev_ap = &(first_autopat[(int)event]);
	for (ap = *prev_ap; ap != NULL; ap = *prev_ap)
	{
	    /* loop over all commands for this pattern */
	    prev_ac = &(ap->cmds);
	    for (ac = *prev_ac; ac != NULL; ac = *prev_ac)
	    {
		/* remove the command if the pattern is to be deleted or when
		 * the command has been marked for deletion */
		if (ap->pat == NULL || ac->cmd == NULL)
		{
		    *prev_ac = ac->next;
		    vim_free(ac->cmd);
		    vim_free(ac);
		}
		else
		    prev_ac = &(ac->next);
	    }

	    /* remove the pattern if it has been marked for deletion */
	    if (ap->pat == NULL)
	    {
		*prev_ap = ap->next;
		vim_regfree(ap->reg_prog);
		vim_free(ap);
	    }
	    else
		prev_ap = &(ap->next);
	}
    }

    au_need_clean = FALSE;
}