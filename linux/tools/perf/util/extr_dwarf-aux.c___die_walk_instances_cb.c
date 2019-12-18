#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct __instance_walk_param {scalar_t__ addr; scalar_t__ retval; int /*<<< orphan*/  data; scalar_t__ (* callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {scalar_t__ addr; } ;
typedef  TYPE_1__ Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_END ; 
 int /*<<< orphan*/  DW_AT_abstract_origin ; 
 scalar_t__ DW_TAG_inlined_subroutine ; 
 int die_get_call_fileno (TYPE_1__*) ; 
 int die_get_call_lineno (TYPE_1__*) ; 
 int die_get_decl_fileno (TYPE_1__*) ; 
 int /*<<< orphan*/ * dwarf_attr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_decl_line (TYPE_1__*,int*) ; 
 TYPE_1__* dwarf_formref_die (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ dwarf_tag (TYPE_1__*) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __die_walk_instances_cb(Dwarf_Die *inst, void *data)
{
	struct __instance_walk_param *iwp = data;
	Dwarf_Attribute attr_mem;
	Dwarf_Die origin_mem;
	Dwarf_Attribute *attr;
	Dwarf_Die *origin;
	int tmp;

	attr = dwarf_attr(inst, DW_AT_abstract_origin, &attr_mem);
	if (attr == NULL)
		return DIE_FIND_CB_CONTINUE;

	origin = dwarf_formref_die(attr, &origin_mem);
	if (origin == NULL || origin->addr != iwp->addr)
		return DIE_FIND_CB_CONTINUE;

	/* Ignore redundant instances */
	if (dwarf_tag(inst) == DW_TAG_inlined_subroutine) {
		dwarf_decl_line(origin, &tmp);
		if (die_get_call_lineno(inst) == tmp) {
			tmp = die_get_decl_fileno(origin);
			if (die_get_call_fileno(inst) == tmp)
				return DIE_FIND_CB_CONTINUE;
		}
	}

	iwp->retval = iwp->callback(inst, iwp->data);

	return (iwp->retval) ? DIE_FIND_CB_END : DIE_FIND_CB_CONTINUE;
}