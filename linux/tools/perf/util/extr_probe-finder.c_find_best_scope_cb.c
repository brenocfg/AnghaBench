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
struct find_scope_param {int found; int line; int diff; int /*<<< orphan*/  die_mem; scalar_t__ function; scalar_t__ file; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 scalar_t__ die_match_name (int /*<<< orphan*/ *,scalar_t__) ; 
 char* dwarf_decl_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_line (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int find_best_scope_cb(Dwarf_Die *fn_die, void *data)
{
	struct find_scope_param *fsp = data;
	const char *file;
	int lno;

	/* Skip if declared file name does not match */
	if (fsp->file) {
		file = dwarf_decl_file(fn_die);
		if (!file || strcmp(fsp->file, file) != 0)
			return 0;
	}
	/* If the function name is given, that's what user expects */
	if (fsp->function) {
		if (die_match_name(fn_die, fsp->function)) {
			memcpy(fsp->die_mem, fn_die, sizeof(Dwarf_Die));
			fsp->found = true;
			return 1;
		}
	} else {
		/* With the line number, find the nearest declared DIE */
		dwarf_decl_line(fn_die, &lno);
		if (lno < fsp->line && fsp->diff > fsp->line - lno) {
			/* Keep a candidate and continue */
			fsp->diff = fsp->line - lno;
			memcpy(fsp->die_mem, fn_die, sizeof(Dwarf_Die));
			fsp->found = true;
		}
	}
	return 0;
}