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
 int KEY_RESIZE ; 
 int /*<<< orphan*/  LINES ; 
 int /*<<< orphan*/  clearoldprompt () ; 
 int /*<<< orphan*/  cleartimeout () ; 
 int getch () ; 
 int /*<<< orphan*/  printprompt (char const*) ; 
 int /*<<< orphan*/  settimeout () ; 
 int /*<<< orphan*/  xlines ; 

__attribute__((used)) static int get_input(const char *prompt)
{
	int r = KEY_RESIZE;

	if (prompt)
		printprompt(prompt);
	cleartimeout();
#ifdef KEY_RESIZE
	while (r == KEY_RESIZE) {
		r = getch();
		if (r == KEY_RESIZE && prompt) {
			clearoldprompt();
			xlines = LINES;
			printprompt(prompt);
		}
	};
#else
	r = getch();
#endif
	settimeout();
	return r;
}