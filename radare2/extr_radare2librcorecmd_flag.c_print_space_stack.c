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
typedef  int /*<<< orphan*/  RFlag ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_kb (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pj_ki (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char const*,...) ; 
 char* r_str_escape (char const*) ; 

__attribute__((used)) static void print_space_stack(RFlag *f, int ordinal, const char *name, bool selected, PJ *pj, int mode) {
	bool first = ordinal == 0;
	switch (mode) {
	case 'j': {
		char *ename = r_str_escape (name);
		if (!ename) {
			return;
		}

		pj_o (pj);
		pj_ki (pj, "ordinal", ordinal);
		pj_ks (pj, "name", ename);
		pj_kb (pj, "selected", selected);
		pj_end (pj);
		free (ename);
		break;
	}
	case '*': {
		const char *fmt = first? "fs %s\n": "fs+%s\n";
		r_cons_printf (fmt, name);
		break;
	}
	default:
		r_cons_printf ("%-2d %s%s\n", ordinal, name, selected? " (selected)": "");
		break;
	}
}