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
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_BLUE ; 
 int /*<<< orphan*/  COLOR_GREEN ; 
 int /*<<< orphan*/  COLOR_RED ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  PT_COLOR_BLUE ; 
 int /*<<< orphan*/  PT_COLOR_BRIGHT ; 
 int /*<<< orphan*/  PT_COLOR_DEFAULT ; 
 int /*<<< orphan*/  PT_COLOR_ERROR ; 
 int /*<<< orphan*/  PT_COLOR_GREEN ; 
 int /*<<< orphan*/  PT_COLOR_HEADER_BAR ; 
 int /*<<< orphan*/  PT_COLOR_RED ; 
 int /*<<< orphan*/  PT_COLOR_YELLOW ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  curs_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  stdscr ; 
 scalar_t__ tui_disabled ; 
 int /*<<< orphan*/  use_default_colors () ; 

void initialize_curses(void)
{
	if (tui_disabled)
		return;

	initscr();
	start_color();
	keypad(stdscr, TRUE);	/* enable keyboard mapping */
	nonl();			/* tell curses not to do NL->CR/NL on output */
	cbreak();		/* take input chars one at a time */
	noecho();		/* dont echo input */
	curs_set(0);		/* turn off cursor */
	use_default_colors();

	init_pair(PT_COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PT_COLOR_HEADER_BAR, COLOR_BLACK, COLOR_WHITE);
	init_pair(PT_COLOR_ERROR, COLOR_BLACK, COLOR_RED);
	init_pair(PT_COLOR_RED, COLOR_WHITE, COLOR_RED);
	init_pair(PT_COLOR_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(PT_COLOR_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(PT_COLOR_BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair(PT_COLOR_BRIGHT, COLOR_WHITE, COLOR_BLACK);

}