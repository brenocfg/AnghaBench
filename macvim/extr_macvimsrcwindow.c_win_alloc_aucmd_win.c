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
 int /*<<< orphan*/  RESET_BINDING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * aucmd_win ; 
 int /*<<< orphan*/  curwin ; 
 int /*<<< orphan*/  new_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * win_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_init_some (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
win_alloc_aucmd_win()
{
    aucmd_win = win_alloc(NULL, TRUE);
    if (aucmd_win != NULL)
    {
	win_init_some(aucmd_win, curwin);
	RESET_BINDING(aucmd_win);
	new_frame(aucmd_win);
    }
}