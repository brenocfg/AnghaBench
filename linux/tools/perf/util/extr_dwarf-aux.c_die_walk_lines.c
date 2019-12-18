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
struct __line_walk_param {int (* callback ) (char const*,int,int /*<<< orphan*/ ,void*) ;void* data; int retval; } ;
typedef  int (* line_walk_callback_t ) (char const*,int,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  Dwarf_Lines ;
typedef  int /*<<< orphan*/  Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 scalar_t__ DW_TAG_compile_unit ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  __die_walk_culines_cb ; 
 int __die_walk_funclines (int /*<<< orphan*/ *,int,int (*) (char const*,int,int /*<<< orphan*/ ,void*),void*) ; 
 scalar_t__ die_find_inlinefunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* dwarf_decl_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_line (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * dwarf_diecu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_getfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct __line_walk_param*,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_getsrclines (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_lineaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_lineno (int /*<<< orphan*/ *,int*) ; 
 char* dwarf_linesrc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwarf_onesrcline (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug2 (char*,...) ; 

int die_walk_lines(Dwarf_Die *rt_die, line_walk_callback_t callback, void *data)
{
	Dwarf_Lines *lines;
	Dwarf_Line *line;
	Dwarf_Addr addr;
	const char *fname, *decf = NULL;
	int lineno, ret = 0;
	int decl = 0, inl;
	Dwarf_Die die_mem, *cu_die;
	size_t nlines, i;

	/* Get the CU die */
	if (dwarf_tag(rt_die) != DW_TAG_compile_unit) {
		cu_die = dwarf_diecu(rt_die, &die_mem, NULL, NULL);
		dwarf_decl_line(rt_die, &decl);
		decf = dwarf_decl_file(rt_die);
	} else
		cu_die = rt_die;
	if (!cu_die) {
		pr_debug2("Failed to get CU from given DIE.\n");
		return -EINVAL;
	}

	/* Get lines list in the CU */
	if (dwarf_getsrclines(cu_die, &lines, &nlines) != 0) {
		pr_debug2("Failed to get source lines on this CU.\n");
		return -ENOENT;
	}
	pr_debug2("Get %zd lines from this CU\n", nlines);

	/* Walk on the lines on lines list */
	for (i = 0; i < nlines; i++) {
		line = dwarf_onesrcline(lines, i);
		if (line == NULL ||
		    dwarf_lineno(line, &lineno) != 0 ||
		    dwarf_lineaddr(line, &addr) != 0) {
			pr_debug2("Failed to get line info. "
				  "Possible error in debuginfo.\n");
			continue;
		}
		/* Filter lines based on address */
		if (rt_die != cu_die) {
			/*
			 * Address filtering
			 * The line is included in given function, and
			 * no inline block includes it.
			 */
			if (!dwarf_haspc(rt_die, addr))
				continue;
			if (die_find_inlinefunc(rt_die, addr, &die_mem)) {
				dwarf_decl_line(&die_mem, &inl);
				if (inl != decl ||
				    decf != dwarf_decl_file(&die_mem))
					continue;
			}
		}
		/* Get source line */
		fname = dwarf_linesrc(line, NULL, NULL);

		ret = callback(fname, lineno, addr, data);
		if (ret != 0)
			return ret;
	}

	/*
	 * Dwarf lines doesn't include function declarations and inlined
	 * subroutines. We have to check functions list or given function.
	 */
	if (rt_die != cu_die)
		/*
		 * Don't need walk functions recursively, because nested
		 * inlined functions don't have lines of the specified DIE.
		 */
		ret = __die_walk_funclines(rt_die, false, callback, data);
	else {
		struct __line_walk_param param = {
			.callback = callback,
			.data = data,
			.retval = 0,
		};
		dwarf_getfuncs(cu_die, __die_walk_culines_cb, &param, 0);
		ret = param.retval;
	}

	return ret;
}