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
 int FAIL ; 
 scalar_t__ FALSE ; 
 int OK ; 
 int /*<<< orphan*/  PtProcessEvent () ; 
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_TIMER_INITIAL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  gui_ph_timer_timeout ; 
 scalar_t__ input_available () ; 
 scalar_t__ is_timeout ; 

int
gui_mch_wait_for_chars(int wtime)
{
    is_timeout = FALSE;

    if (wtime > 0)
	PtSetResource(gui_ph_timer_timeout, Pt_ARG_TIMER_INITIAL, wtime, 0);

    while (1)
    {
	PtProcessEvent();
	if (input_available())
	{
	    PtSetResource(gui_ph_timer_timeout, Pt_ARG_TIMER_INITIAL, 0, 0);
	    return OK;
	}
	else if (is_timeout == TRUE)
	    return FAIL;
    }
}