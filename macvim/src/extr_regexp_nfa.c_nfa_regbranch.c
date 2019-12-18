#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ) ; 
 scalar_t__ FAIL ; 
 int Magic (char) ; 
 int /*<<< orphan*/  NFA_CONCAT ; 
 int /*<<< orphan*/  NFA_EMPTY ; 
 int /*<<< orphan*/  NFA_NOPEN ; 
 int /*<<< orphan*/  NFA_PREV_ATOM_NO_WIDTH ; 
 int OK ; 
 scalar_t__ nfa_regconcat () ; 
 int peekchr () ; 
 scalar_t__ post_ptr ; 
 scalar_t__ post_start ; 
 int /*<<< orphan*/  skipchr () ; 

__attribute__((used)) static int
nfa_regbranch()
{
    int		ch;
    int		old_post_pos;

    old_post_pos = (int)(post_ptr - post_start);

    /* First branch, possibly the only one */
    if (nfa_regconcat() == FAIL)
	return FAIL;

    ch = peekchr();
    /* Try next concats */
    while (ch == Magic('&'))
    {
	skipchr();
	EMIT(NFA_NOPEN);
	EMIT(NFA_PREV_ATOM_NO_WIDTH);
	old_post_pos = (int)(post_ptr - post_start);
	if (nfa_regconcat() == FAIL)
	    return FAIL;
	/* if concat is empty do emit a node */
	if (old_post_pos == (int)(post_ptr - post_start))
	    EMIT(NFA_EMPTY);
	EMIT(NFA_CONCAT);
	ch = peekchr();
    }

    /* if a branch is empty, emit one node for it */
    if (old_post_pos == (int)(post_ptr - post_start))
	EMIT(NFA_EMPTY);

    return OK;
}