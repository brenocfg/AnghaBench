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
struct probe_finder {int /*<<< orphan*/  addr; int /*<<< orphan*/  machine; int /*<<< orphan*/  sp_die; int /*<<< orphan*/  fb_ops; } ;
struct local_vars_finder {size_t nargs; struct probe_finder* pf; TYPE_1__* args; int /*<<< orphan*/  ret; scalar_t__ vars; } ;
struct TYPE_2__ {char* var; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_END ; 
 int DIE_FIND_CB_SIBLING ; 
 int DW_TAG_formal_parameter ; 
 int DW_TAG_variable ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ convert_variable_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 

__attribute__((used)) static int copy_variables_cb(Dwarf_Die *die_mem, void *data)
{
	struct local_vars_finder *vf = data;
	struct probe_finder *pf = vf->pf;
	int tag;

	tag = dwarf_tag(die_mem);
	if (tag == DW_TAG_formal_parameter ||
	    (tag == DW_TAG_variable && vf->vars)) {
		if (convert_variable_location(die_mem, vf->pf->addr,
					      vf->pf->fb_ops, &pf->sp_die,
					      pf->machine, NULL) == 0) {
			vf->args[vf->nargs].var = (char *)dwarf_diename(die_mem);
			if (vf->args[vf->nargs].var == NULL) {
				vf->ret = -ENOMEM;
				return DIE_FIND_CB_END;
			}
			pr_debug(" %s", vf->args[vf->nargs].var);
			vf->nargs++;
		}
	}

	if (dwarf_haspc(die_mem, vf->pf->addr))
		return DIE_FIND_CB_CONTINUE;
	else
		return DIE_FIND_CB_SIBLING;
}