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
 int /*<<< orphan*/  CURSOR_RESTORE () ; 
 int /*<<< orphan*/  CURSOR_SHOW () ; 
 int /*<<< orphan*/  SCREEN_RESTORE () ; 
 scalar_t__ clearScr ; 
 int /*<<< orphan*/  nmstermio_set_terminal (int) ; 

void nmstermio_restore_terminal(void) {
	
	// Restore screen and cursor is clearSrc is set
	if (clearScr) {
		SCREEN_RESTORE();
		CURSOR_SHOW();
		CURSOR_RESTORE();
	}
	
	// Turn on line buffering and echo
	nmstermio_set_terminal(1);
}