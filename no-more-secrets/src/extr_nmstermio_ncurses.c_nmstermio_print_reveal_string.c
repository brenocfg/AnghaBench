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
 int /*<<< orphan*/  A_BOLD ; 
 int /*<<< orphan*/  COLOR_PAIR (int) ; 
 int /*<<< orphan*/  addstr (char*) ; 
 int /*<<< orphan*/  attroff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attron (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foregroundColor ; 
 scalar_t__ has_colors () ; 

void nmstermio_print_reveal_string(char *s, int colorOn) {
	(void) colorOn;
	(void) foregroundColor;

	// Set bold and foreground color for character reveal
	attron(A_BOLD);
	if (has_colors())
		attron(COLOR_PAIR(1));
	
	// print source character
	addstr(s);
	
	// Unset foreground color
	if (has_colors())
		attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
}