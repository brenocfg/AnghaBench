#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_3__ {int col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int CTRL_X_OMNI ; 
 int K_BS ; 
 int NUL ; 
 scalar_t__ compl_col ; 
 int /*<<< orphan*/ * compl_curr_match ; 
 int /*<<< orphan*/ * compl_leader ; 
 scalar_t__ compl_length ; 
 int /*<<< orphan*/ * compl_shown_match ; 
 int ctrl_x_mode ; 
 TYPE_2__* curwin ; 
 scalar_t__ ins_compl_need_restart () ; 
 int /*<<< orphan*/  ins_compl_new_leader () ; 
 int /*<<< orphan*/  ins_compl_restart () ; 
 int /*<<< orphan*/  mb_ptr_back (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ml_get_curline () ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vim_strnsave (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
ins_compl_bs()
{
    char_u	*line;
    char_u	*p;

    line = ml_get_curline();
    p = line + curwin->w_cursor.col;
    mb_ptr_back(line, p);

    /* Stop completion when the whole word was deleted.  For Omni completion
     * allow the word to be deleted, we won't match everything. */
    if ((int)(p - line) - (int)compl_col < 0
	    || ((int)(p - line) - (int)compl_col == 0
		&& (ctrl_x_mode & CTRL_X_OMNI) == 0))
	return K_BS;

    /* Deleted more than what was used to find matches or didn't finish
     * finding all matches: need to look for matches all over again. */
    if (curwin->w_cursor.col <= compl_col + compl_length
						  || ins_compl_need_restart())
	ins_compl_restart();

    vim_free(compl_leader);
    compl_leader = vim_strnsave(line + compl_col, (int)(p - line) - compl_col);
    if (compl_leader != NULL)
    {
	ins_compl_new_leader();
	if (compl_shown_match != NULL)
	    /* Make sure current match is not a hidden item. */
	    compl_curr_match = compl_shown_match;
	return NUL;
    }
    return K_BS;
}