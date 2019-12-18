#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct probe_finder {scalar_t__ addr; int /*<<< orphan*/  lno; int /*<<< orphan*/  fname; TYPE_1__* pev; } ;
struct perf_probe_point {scalar_t__ offset; int /*<<< orphan*/  function; scalar_t__ lazy_line; scalar_t__ line; scalar_t__ file; } ;
struct dwarf_callback_param {int /*<<< orphan*/  retval; struct probe_finder* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  no_inlines; } ;
struct TYPE_3__ {struct perf_probe_point point; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  call_probe_finder (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  die_is_func_def (int /*<<< orphan*/ *) ; 
 scalar_t__ die_is_func_instance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_match_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_walk_instances (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dwarf_decl_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_dieoffset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_entrypc (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  find_probe_point_by_line (struct probe_finder*) ; 
 int /*<<< orphan*/  find_probe_point_lazy (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_2__ probe_conf ; 
 int /*<<< orphan*/  probe_point_inline_cb ; 
 int /*<<< orphan*/  skip_prologue (int /*<<< orphan*/ *,struct probe_finder*) ; 
 scalar_t__ strisglob (int /*<<< orphan*/ ) ; 
 scalar_t__ strtailcmp (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_point_search_cb(Dwarf_Die *sp_die, void *data)
{
	struct dwarf_callback_param *param = data;
	struct probe_finder *pf = param->data;
	struct perf_probe_point *pp = &pf->pev->point;

	/* Check tag and diename */
	if (!die_is_func_def(sp_die) ||
	    !die_match_name(sp_die, pp->function))
		return DWARF_CB_OK;

	/* Check declared file */
	if (pp->file && strtailcmp(pp->file, dwarf_decl_file(sp_die)))
		return DWARF_CB_OK;

	pr_debug("Matched function: %s [%lx]\n", dwarf_diename(sp_die),
		 (unsigned long)dwarf_dieoffset(sp_die));
	pf->fname = dwarf_decl_file(sp_die);
	if (pp->line) { /* Function relative line */
		dwarf_decl_line(sp_die, &pf->lno);
		pf->lno += pp->line;
		param->retval = find_probe_point_by_line(pf);
	} else if (die_is_func_instance(sp_die)) {
		/* Instances always have the entry address */
		dwarf_entrypc(sp_die, &pf->addr);
		/* But in some case the entry address is 0 */
		if (pf->addr == 0) {
			pr_debug("%s has no entry PC. Skipped\n",
				 dwarf_diename(sp_die));
			param->retval = 0;
		/* Real function */
		} else if (pp->lazy_line)
			param->retval = find_probe_point_lazy(sp_die, pf);
		else {
			skip_prologue(sp_die, pf);
			pf->addr += pp->offset;
			/* TODO: Check the address in this function */
			param->retval = call_probe_finder(sp_die, pf);
		}
	} else if (!probe_conf.no_inlines) {
		/* Inlined function: search instances */
		param->retval = die_walk_instances(sp_die,
					probe_point_inline_cb, (void *)pf);
		/* This could be a non-existed inline definition */
		if (param->retval == -ENOENT)
			param->retval = 0;
	}

	/* We need to find other candidates */
	if (strisglob(pp->function) && param->retval >= 0) {
		param->retval = 0;	/* We have to clear the result */
		return DWARF_CB_OK;
	}

	return DWARF_CB_ABORT; /* Exit; no same symbol in this CU. */
}