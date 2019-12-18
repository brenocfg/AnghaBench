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
typedef  int /*<<< orphan*/  ypos ;
typedef  int /*<<< orphan*/  xpos ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 void* r_cons_readchar () ; 
 int /*<<< orphan*/  r_cons_set_click (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __parseMouseEvent() {
	char xpos[32];
	char ypos[32];
	(void)r_cons_readchar (); // skip first char
	int ch2 = r_cons_readchar ();

	// [32M - mousedown
	// [35M - mouseup
	if (ch2 == ';') {
		int i;
		// read until next ;
		for (i = 0; i < sizeof (xpos); i++) {
			char ch = r_cons_readchar ();
			if (ch == ';' || ch == 'M') {
				break;
			}
			xpos[i] = ch;
		}
		xpos[i] = 0;
		for (i = 0; i < sizeof (ypos); i++) {
			char ch = r_cons_readchar ();
			if (ch == ';' || ch == 'M') {
				break;
			}
			ypos[i] = ch;
		}
		ypos[i] = 0;
		r_cons_set_click (atoi (xpos), atoi (ypos));
		(void) r_cons_readchar ();
		// ignored
		int ch = r_cons_readchar ();
		if (ch == 27) {
			ch = r_cons_readchar (); // '['
		}
		if (ch == '[') {
			do {
				ch = r_cons_readchar (); // '3'
			} while (ch != 'M');
		}
	}
	return 0;
}