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
 scalar_t__ BLINK_NONE ; 
 scalar_t__ BLINK_OFF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_TIMER_INITIAL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ blink_state ; 
 int /*<<< orphan*/  gui_ph_timer_cursor ; 
 int /*<<< orphan*/  gui_update_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gui_mch_stop_blink(void)
{
    PtSetResource(gui_ph_timer_cursor, Pt_ARG_TIMER_INITIAL, 0, 0);

    if (blink_state == BLINK_OFF)
	gui_update_cursor(TRUE, FALSE);

    blink_state = BLINK_NONE;
}