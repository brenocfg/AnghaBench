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
 scalar_t__ FAIL ; 
 int OK ; 
 scalar_t__ win_alloc_firstwin (int /*<<< orphan*/ *) ; 

int
win_alloc_first()
{
    if (win_alloc_firstwin(NULL) == FAIL)
	return FAIL;

#ifdef FEAT_WINDOWS
    first_tabpage = alloc_tabpage();
    if (first_tabpage == NULL)
	return FAIL;
    first_tabpage->tp_topframe = topframe;
    curtab = first_tabpage;
#endif

    return OK;
}