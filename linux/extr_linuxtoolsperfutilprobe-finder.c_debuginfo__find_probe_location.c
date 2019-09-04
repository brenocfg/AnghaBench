#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pubname_callback_param {scalar_t__ found; int /*<<< orphan*/ * sp_die; int /*<<< orphan*/ * cu_die; scalar_t__ file; scalar_t__ function; } ;
struct probe_finder {int /*<<< orphan*/ * lcache; int /*<<< orphan*/  lno; int /*<<< orphan*/  cu_die; int /*<<< orphan*/ * fname; int /*<<< orphan*/  sp_die; TYPE_1__* pev; } ;
struct perf_probe_point {int /*<<< orphan*/  line; scalar_t__ lazy_line; scalar_t__ function; scalar_t__ file; } ;
struct dwarf_callback_param {struct probe_finder* data; } ;
struct debuginfo {int /*<<< orphan*/  dbg; } ;
struct TYPE_2__ {struct perf_probe_point point; } ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * cu_find_realpath (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dwarf_getpubnames (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pubname_callback_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_nextcu (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwarf_offdie (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int find_probe_point_by_func (struct probe_finder*) ; 
 int find_probe_point_by_line (struct probe_finder*) ; 
 int find_probe_point_lazy (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  intlist__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intlist__new (int /*<<< orphan*/ *) ; 
 int probe_point_search_cb (int /*<<< orphan*/ *,struct dwarf_callback_param*) ; 
 int /*<<< orphan*/  pubname_search_cb ; 
 int /*<<< orphan*/  strisglob (scalar_t__) ; 

__attribute__((used)) static int debuginfo__find_probe_location(struct debuginfo *dbg,
				  struct probe_finder *pf)
{
	struct perf_probe_point *pp = &pf->pev->point;
	Dwarf_Off off, noff;
	size_t cuhl;
	Dwarf_Die *diep;
	int ret = 0;

	off = 0;
	pf->lcache = intlist__new(NULL);
	if (!pf->lcache)
		return -ENOMEM;

	/* Fastpath: lookup by function name from .debug_pubnames section */
	if (pp->function && !strisglob(pp->function)) {
		struct pubname_callback_param pubname_param = {
			.function = pp->function,
			.file	  = pp->file,
			.cu_die	  = &pf->cu_die,
			.sp_die	  = &pf->sp_die,
			.found	  = 0,
		};
		struct dwarf_callback_param probe_param = {
			.data = pf,
		};

		dwarf_getpubnames(dbg->dbg, pubname_search_cb,
				  &pubname_param, 0);
		if (pubname_param.found) {
			ret = probe_point_search_cb(&pf->sp_die, &probe_param);
			if (ret)
				goto found;
		}
	}

	/* Loop on CUs (Compilation Unit) */
	while (!dwarf_nextcu(dbg->dbg, off, &noff, &cuhl, NULL, NULL, NULL)) {
		/* Get the DIE(Debugging Information Entry) of this CU */
		diep = dwarf_offdie(dbg->dbg, off + cuhl, &pf->cu_die);
		if (!diep)
			continue;

		/* Check if target file is included. */
		if (pp->file)
			pf->fname = cu_find_realpath(&pf->cu_die, pp->file);
		else
			pf->fname = NULL;

		if (!pp->file || pf->fname) {
			if (pp->function)
				ret = find_probe_point_by_func(pf);
			else if (pp->lazy_line)
				ret = find_probe_point_lazy(&pf->cu_die, pf);
			else {
				pf->lno = pp->line;
				ret = find_probe_point_by_line(pf);
			}
			if (ret < 0)
				break;
		}
		off = noff;
	}

found:
	intlist__delete(pf->lcache);
	pf->lcache = NULL;

	return ret;
}