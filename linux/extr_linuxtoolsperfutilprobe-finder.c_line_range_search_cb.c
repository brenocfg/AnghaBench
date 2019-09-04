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
struct line_range {scalar_t__ offset; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  function; scalar_t__ file; } ;
struct line_finder {scalar_t__ fname; scalar_t__ lno_s; scalar_t__ lno_e; struct line_range* lr; } ;
struct dwarf_callback_param {int /*<<< orphan*/  retval; struct line_finder* data; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 void* INT_MAX ; 
 scalar_t__ die_is_func_def (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_is_func_instance (int /*<<< orphan*/ *) ; 
 scalar_t__ die_match_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_walk_instances (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct line_finder*) ; 
 scalar_t__ dwarf_decl_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_line (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  find_line_range_by_line (int /*<<< orphan*/ *,struct line_finder*) ; 
 int /*<<< orphan*/  line_range_inline_cb ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ strtailcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int line_range_search_cb(Dwarf_Die *sp_die, void *data)
{
	struct dwarf_callback_param *param = data;
	struct line_finder *lf = param->data;
	struct line_range *lr = lf->lr;

	/* Check declared file */
	if (lr->file && strtailcmp(lr->file, dwarf_decl_file(sp_die)))
		return DWARF_CB_OK;

	if (die_is_func_def(sp_die) &&
	    die_match_name(sp_die, lr->function)) {
		lf->fname = dwarf_decl_file(sp_die);
		dwarf_decl_line(sp_die, &lr->offset);
		pr_debug("fname: %s, lineno:%d\n", lf->fname, lr->offset);
		lf->lno_s = lr->offset + lr->start;
		if (lf->lno_s < 0)	/* Overflow */
			lf->lno_s = INT_MAX;
		lf->lno_e = lr->offset + lr->end;
		if (lf->lno_e < 0)	/* Overflow */
			lf->lno_e = INT_MAX;
		pr_debug("New line range: %d to %d\n", lf->lno_s, lf->lno_e);
		lr->start = lf->lno_s;
		lr->end = lf->lno_e;
		if (!die_is_func_instance(sp_die))
			param->retval = die_walk_instances(sp_die,
						line_range_inline_cb, lf);
		else
			param->retval = find_line_range_by_line(sp_die, lf);
		return DWARF_CB_ABORT;
	}
	return DWARF_CB_OK;
}