#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct probe_finder {TYPE_1__* pvar; int /*<<< orphan*/  cu_die; int /*<<< orphan*/  addr; TYPE_2__* tvar; } ;
struct TYPE_5__ {char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  var; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int convert_variable (int /*<<< orphan*/ *,struct probe_finder*) ; 
 int copy_to_probe_trace_arg (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  die_find_variable_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_c_varname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (scalar_t__) ; 
 char* synthesize_perf_probe_arg (TYPE_1__*) ; 

__attribute__((used)) static int find_variable(Dwarf_Die *sc_die, struct probe_finder *pf)
{
	Dwarf_Die vr_die;
	char *buf, *ptr;
	int ret = 0;

	/* Copy raw parameters */
	if (!is_c_varname(pf->pvar->var))
		return copy_to_probe_trace_arg(pf->tvar, pf->pvar);

	if (pf->pvar->name)
		pf->tvar->name = strdup(pf->pvar->name);
	else {
		buf = synthesize_perf_probe_arg(pf->pvar);
		if (!buf)
			return -ENOMEM;
		ptr = strchr(buf, ':');	/* Change type separator to _ */
		if (ptr)
			*ptr = '_';
		pf->tvar->name = buf;
	}
	if (pf->tvar->name == NULL)
		return -ENOMEM;

	pr_debug("Searching '%s' variable in context.\n", pf->pvar->var);
	/* Search child die for local variables and parameters. */
	if (!die_find_variable_at(sc_die, pf->pvar->var, pf->addr, &vr_die)) {
		/* Search again in global variables */
		if (!die_find_variable_at(&pf->cu_die, pf->pvar->var,
						0, &vr_die)) {
			pr_warning("Failed to find '%s' in this function.\n",
				   pf->pvar->var);
			ret = -ENOENT;
		}
	}
	if (ret >= 0)
		ret = convert_variable(&vr_die, pf);

	return ret;
}