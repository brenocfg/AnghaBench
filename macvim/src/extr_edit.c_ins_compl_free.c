#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cp_flags; struct TYPE_7__** cp_text; struct TYPE_7__* cp_fname; struct TYPE_7__* cp_str; struct TYPE_7__* cp_next; } ;
typedef  TYPE_1__ compl_T ;

/* Variables and functions */
 int CPT_COUNT ; 
 int FREE_FNAME ; 
 TYPE_1__* compl_curr_match ; 
 TYPE_1__* compl_first_match ; 
 TYPE_1__* compl_leader ; 
 TYPE_1__* compl_pattern ; 
 int /*<<< orphan*/ * compl_shown_match ; 
 int /*<<< orphan*/  ins_compl_del_pum () ; 
 int /*<<< orphan*/  pum_clear () ; 
 int /*<<< orphan*/  vim_free (TYPE_1__*) ; 

__attribute__((used)) static void
ins_compl_free()
{
    compl_T *match;
    int	    i;

    vim_free(compl_pattern);
    compl_pattern = NULL;
    vim_free(compl_leader);
    compl_leader = NULL;

    if (compl_first_match == NULL)
	return;

    ins_compl_del_pum();
    pum_clear();

    compl_curr_match = compl_first_match;
    do
    {
	match = compl_curr_match;
	compl_curr_match = compl_curr_match->cp_next;
	vim_free(match->cp_str);
	/* several entries may use the same fname, free it just once. */
	if (match->cp_flags & FREE_FNAME)
	    vim_free(match->cp_fname);
	for (i = 0; i < CPT_COUNT; ++i)
	    vim_free(match->cp_text[i]);
	vim_free(match);
    } while (compl_curr_match != NULL && compl_curr_match != compl_first_match);
    compl_first_match = compl_curr_match = NULL;
    compl_shown_match = NULL;
}