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
 int /*<<< orphan*/  CLEAR_SCR () ; 
 int /*<<< orphan*/  CURSOR_HIDE () ; 
 int /*<<< orphan*/  CURSOR_HOME () ; 
 int /*<<< orphan*/  CURSOR_SAVE () ; 
 int /*<<< orphan*/  SCREEN_SAVE () ; 
 scalar_t__ clearScr ; 
 int /*<<< orphan*/  nmstermio_set_terminal (int /*<<< orphan*/ ) ; 

void nmstermio_init_terminal(void) {

	// Turn off line buffering and echo
	nmstermio_set_terminal(0);
	
	// Save terminal state, clear screen, and home/hide the cursor
	if (clearScr) {
		CURSOR_SAVE();
		SCREEN_SAVE();
		CLEAR_SCR();
		CURSOR_HOME();
		CURSOR_HIDE();
	}
}