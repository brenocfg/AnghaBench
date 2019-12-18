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
struct probe_finder {TYPE_1__* pvar; TYPE_2__* tvar; int /*<<< orphan*/  machine; int /*<<< orphan*/  sp_die; int /*<<< orphan*/  fb_ops; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_access; int /*<<< orphan*/  type; scalar_t__ field; int /*<<< orphan*/  var; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUP ; 
 int convert_variable_fields (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int convert_variable_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int convert_variable_type (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int convert_variable(Dwarf_Die *vr_die, struct probe_finder *pf)
{
	Dwarf_Die die_mem;
	int ret;

	pr_debug("Converting variable %s into trace event.\n",
		 dwarf_diename(vr_die));

	ret = convert_variable_location(vr_die, pf->addr, pf->fb_ops,
					&pf->sp_die, pf->machine, pf->tvar);
	if (ret == -ENOENT || ret == -EINVAL) {
		pr_err("Failed to find the location of the '%s' variable at this address.\n"
		       " Perhaps it has been optimized out.\n"
		       " Use -V with the --range option to show '%s' location range.\n",
		       pf->pvar->var, pf->pvar->var);
	} else if (ret == -ENOTSUP)
		pr_err("Sorry, we don't support this variable location yet.\n");
	else if (ret == 0 && pf->pvar->field) {
		ret = convert_variable_fields(vr_die, pf->pvar->var,
					      pf->pvar->field, &pf->tvar->ref,
					      &die_mem, pf->pvar->user_access);
		vr_die = &die_mem;
	}
	if (ret == 0)
		ret = convert_variable_type(vr_die, pf->tvar, pf->pvar->type,
					    pf->pvar->user_access);
	/* *expr will be cached in libdw. Don't free it. */
	return ret;
}