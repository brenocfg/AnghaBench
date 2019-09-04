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
struct probe_finder {int lno; int /*<<< orphan*/  addr; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int ENOENT ; 
 int call_probe_finder (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/ * find_best_scope (struct probe_finder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ strtailcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_point_line_walker(const char *fname, int lineno,
				   Dwarf_Addr addr, void *data)
{
	struct probe_finder *pf = data;
	Dwarf_Die *sc_die, die_mem;
	int ret;

	if (lineno != pf->lno || strtailcmp(fname, pf->fname) != 0)
		return 0;

	pf->addr = addr;
	sc_die = find_best_scope(pf, &die_mem);
	if (!sc_die) {
		pr_warning("Failed to find scope of probe point.\n");
		return -ENOENT;
	}

	ret = call_probe_finder(sc_die, pf);

	/* Continue if no error, because the line will be in inline function */
	return ret < 0 ? ret : 0;
}