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
struct __line_walk_param {scalar_t__ retval; scalar_t__ (* callback ) (char const*,int,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; int /*<<< orphan*/  recursive; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Addr ;

/* Variables and functions */
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_END ; 
 int DIE_FIND_CB_SIBLING ; 
 scalar_t__ DW_TAG_inlined_subroutine ; 
 char* die_get_call_file (int /*<<< orphan*/ *) ; 
 int die_get_call_lineno (int /*<<< orphan*/ *) ; 
 char* dwarf_decl_file (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_decl_line (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (char const*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (char const*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __die_walk_funclines_cb(Dwarf_Die *in_die, void *data)
{
	struct __line_walk_param *lw = data;
	Dwarf_Addr addr = 0;
	const char *fname;
	int lineno;

	if (dwarf_tag(in_die) == DW_TAG_inlined_subroutine) {
		fname = die_get_call_file(in_die);
		lineno = die_get_call_lineno(in_die);
		if (fname && lineno > 0 && dwarf_entrypc(in_die, &addr) == 0) {
			lw->retval = lw->callback(fname, lineno, addr, lw->data);
			if (lw->retval != 0)
				return DIE_FIND_CB_END;
		}
	}
	if (!lw->recursive)
		/* Don't need to search recursively */
		return DIE_FIND_CB_SIBLING;

	if (addr) {
		fname = dwarf_decl_file(in_die);
		if (fname && dwarf_decl_line(in_die, &lineno) == 0) {
			lw->retval = lw->callback(fname, lineno, addr, lw->data);
			if (lw->retval != 0)
				return DIE_FIND_CB_END;
		}
	}

	/* Continue to search nested inlined function call-sites */
	return DIE_FIND_CB_CONTINUE;
}