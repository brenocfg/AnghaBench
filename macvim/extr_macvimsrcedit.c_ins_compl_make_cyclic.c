#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* cp_prev; struct TYPE_3__* cp_next; } ;
typedef  TYPE_1__ compl_T ;

/* Variables and functions */
 TYPE_1__* compl_first_match ; 

__attribute__((used)) static int
ins_compl_make_cyclic()
{
    compl_T *match;
    int	    count = 0;

    if (compl_first_match != NULL)
    {
	/*
	 * Find the end of the list.
	 */
	match = compl_first_match;
	/* there's always an entry for the compl_orig_text, it doesn't count. */
	while (match->cp_next != NULL && match->cp_next != compl_first_match)
	{
	    match = match->cp_next;
	    ++count;
	}
	match->cp_next = compl_first_match;
	compl_first_match->cp_prev = match;
    }
    return count;
}