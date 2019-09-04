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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ composing_hangul ; 
 int /*<<< orphan*/  composing_hangul_buffer ; 
 int /*<<< orphan*/  gui_update_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hangul_input_state_get () ; 
 int /*<<< orphan*/  hangul_input_state_set (int) ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  push_raw_key (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setcursor () ; 
 scalar_t__ showmode () ; 

void
hangul_input_state_toggle()
{
    if (hangul_input_state_get())
    {
	hangul_input_state_set(0);
	if (composing_hangul)
	{
	    push_raw_key(composing_hangul_buffer, 2);
	    composing_hangul = 0;
	}
    }
    else
	hangul_input_state_set(1);

    if (showmode())
    {
	setcursor();
	out_flush();
    }

    gui_update_cursor(TRUE, FALSE);
}