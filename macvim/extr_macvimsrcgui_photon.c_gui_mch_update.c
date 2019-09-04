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
 int /*<<< orphan*/  PtAppAddWorkProc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  PtProcessEvent () ; 
 int TRUE ; 
 int /*<<< orphan*/  exit_gui_mch_update ; 
 int /*<<< orphan*/  vim_is_input_buf_full () ; 

void
gui_mch_update(void)
{
    int working = TRUE;

    PtAppAddWorkProc(NULL, exit_gui_mch_update, &working);
    while ((working == TRUE) && !vim_is_input_buf_full())
    {
	PtProcessEvent();
    }
}