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
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  curtheme ; 
 int getNext ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*,char const*) ; 
 int /*<<< orphan*/  r_cons_println (char const*) ; 
 int /*<<< orphan*/  r_str_dup (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_lchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool nextpal_item(RCore *core, int mode, const char *file, int ctr) {
	const char *fn = r_str_lchr (file, '/');
	if (!fn) fn = file;
	switch (mode) {
	case 'j': // json
		r_cons_printf ("%s\"%s\"", ctr?",":"", fn);
		break;
	case 'l': // list
		r_cons_println (fn);
		break;
	case 'p': // previous
		// TODO: move logic here
		break;
	case 'n': // next
		if (getNext) {
			curtheme = r_str_dup (curtheme, fn);
			getNext = false;
			return false;
		} else if (curtheme) {
			if (!strcmp (curtheme, fn)) {
				getNext = true;
			}
		} else {
			curtheme = r_str_dup (curtheme, fn);
			return false;
		}
		break;
	}
	return true;
}