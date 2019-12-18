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
struct perf_probe_point {int line; unsigned long offset; int /*<<< orphan*/ * function; int /*<<< orphan*/ * file; } ;
struct debuginfo {int /*<<< orphan*/  dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  unsigned long Dwarf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cu_find_lineinfo (int /*<<< orphan*/ *,unsigned long,char const**,int*) ; 
 scalar_t__ debuginfo__get_text_offset (struct debuginfo*,unsigned long*,int) ; 
 scalar_t__ die_find_realfunc (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ die_find_top_inlinefunc (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 char* die_get_call_file (int /*<<< orphan*/ *) ; 
 int die_get_call_lineno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_addrdie (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 char* dwarf_decl_file (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_decl_line (int /*<<< orphan*/ *,int*) ; 
 char* dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_entrypc (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  pr_warning (char*,unsigned long) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

int debuginfo__find_probe_point(struct debuginfo *dbg, unsigned long addr,
				struct perf_probe_point *ppt)
{
	Dwarf_Die cudie, spdie, indie;
	Dwarf_Addr _addr = 0, baseaddr = 0;
	const char *fname = NULL, *func = NULL, *basefunc = NULL, *tmp;
	int baseline = 0, lineno = 0, ret = 0;

	/* We always need to relocate the address for aranges */
	if (debuginfo__get_text_offset(dbg, &baseaddr, false) == 0)
		addr += baseaddr;
	/* Find cu die */
	if (!dwarf_addrdie(dbg->dbg, (Dwarf_Addr)addr, &cudie)) {
		pr_warning("Failed to find debug information for address %lx\n",
			   addr);
		ret = -EINVAL;
		goto end;
	}

	/* Find a corresponding line (filename and lineno) */
	cu_find_lineinfo(&cudie, addr, &fname, &lineno);
	/* Don't care whether it failed or not */

	/* Find a corresponding function (name, baseline and baseaddr) */
	if (die_find_realfunc(&cudie, (Dwarf_Addr)addr, &spdie)) {
		/* Get function entry information */
		func = basefunc = dwarf_diename(&spdie);
		if (!func ||
		    dwarf_entrypc(&spdie, &baseaddr) != 0 ||
		    dwarf_decl_line(&spdie, &baseline) != 0) {
			lineno = 0;
			goto post;
		}

		fname = dwarf_decl_file(&spdie);
		if (addr == (unsigned long)baseaddr) {
			/* Function entry - Relative line number is 0 */
			lineno = baseline;
			goto post;
		}

		/* Track down the inline functions step by step */
		while (die_find_top_inlinefunc(&spdie, (Dwarf_Addr)addr,
						&indie)) {
			/* There is an inline function */
			if (dwarf_entrypc(&indie, &_addr) == 0 &&
			    _addr == addr) {
				/*
				 * addr is at an inline function entry.
				 * In this case, lineno should be the call-site
				 * line number. (overwrite lineinfo)
				 */
				lineno = die_get_call_lineno(&indie);
				fname = die_get_call_file(&indie);
				break;
			} else {
				/*
				 * addr is in an inline function body.
				 * Since lineno points one of the lines
				 * of the inline function, baseline should
				 * be the entry line of the inline function.
				 */
				tmp = dwarf_diename(&indie);
				if (!tmp ||
				    dwarf_decl_line(&indie, &baseline) != 0)
					break;
				func = tmp;
				spdie = indie;
			}
		}
		/* Verify the lineno and baseline are in a same file */
		tmp = dwarf_decl_file(&spdie);
		if (!tmp || strcmp(tmp, fname) != 0)
			lineno = 0;
	}

post:
	/* Make a relative line number or an offset */
	if (lineno)
		ppt->line = lineno - baseline;
	else if (basefunc) {
		ppt->offset = addr - (unsigned long)baseaddr;
		func = basefunc;
	}

	/* Duplicate strings */
	if (func) {
		ppt->function = strdup(func);
		if (ppt->function == NULL) {
			ret = -ENOMEM;
			goto end;
		}
	}
	if (fname) {
		ppt->file = strdup(fname);
		if (ppt->file == NULL) {
			zfree(&ppt->function);
			ret = -ENOMEM;
			goto end;
		}
	}
end:
	if (ret == 0 && (fname || func))
		ret = 1;	/* Found a point */
	return ret;
}