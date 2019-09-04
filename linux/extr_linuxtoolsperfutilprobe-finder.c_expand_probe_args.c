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
struct probe_finder {TYPE_1__* pev; } ;
struct perf_probe_arg {int var; } ;
struct local_vars_finder {int vars; scalar_t__ ret; int nargs; int /*<<< orphan*/  max_args; struct perf_probe_arg* args; struct probe_finder* pf; } ;
struct TYPE_2__ {int nargs; struct perf_probe_arg* args; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PROBE_ARGS ; 
 int /*<<< orphan*/  PROBE_ARG_PARAMS ; 
 int /*<<< orphan*/  PROBE_ARG_VARS ; 
 int /*<<< orphan*/  copy_variables_cb ; 
 int /*<<< orphan*/  die_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 scalar_t__ strcmp (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int expand_probe_args(Dwarf_Die *sc_die, struct probe_finder *pf,
			     struct perf_probe_arg *args)
{
	Dwarf_Die die_mem;
	int i;
	int n = 0;
	struct local_vars_finder vf = {.pf = pf, .args = args, .vars = false,
				.max_args = MAX_PROBE_ARGS, .ret = 0};

	for (i = 0; i < pf->pev->nargs; i++) {
		/* var never be NULL */
		if (strcmp(pf->pev->args[i].var, PROBE_ARG_VARS) == 0)
			vf.vars = true;
		else if (strcmp(pf->pev->args[i].var, PROBE_ARG_PARAMS) != 0) {
			/* Copy normal argument */
			args[n] = pf->pev->args[i];
			n++;
			continue;
		}
		pr_debug("Expanding %s into:", pf->pev->args[i].var);
		vf.nargs = n;
		/* Special local variables */
		die_find_child(sc_die, copy_variables_cb, (void *)&vf,
			       &die_mem);
		pr_debug(" (%d)\n", vf.nargs - n);
		if (vf.ret < 0)
			return vf.ret;
		n = vf.nargs;
	}
	return n;
}