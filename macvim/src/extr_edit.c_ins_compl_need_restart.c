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
 scalar_t__ CTRL_X_FUNCTION ; 
 scalar_t__ CTRL_X_OMNI ; 
 scalar_t__ compl_opt_refresh_always ; 
 scalar_t__ compl_was_interrupted ; 
 scalar_t__ ctrl_x_mode ; 

__attribute__((used)) static int
ins_compl_need_restart()
{
    /* Return TRUE if we didn't complete finding matches or when the
     * 'completefunc' returned "always" in the "refresh" dictionary item. */
    return compl_was_interrupted
	|| ((ctrl_x_mode == CTRL_X_FUNCTION || ctrl_x_mode == CTRL_X_OMNI)
						  && compl_opt_refresh_always);
}