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
struct __find_variable_param {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_END ; 
 int DIE_FIND_CB_SIBLING ; 
 int /*<<< orphan*/  DW_AT_external ; 
 int /*<<< orphan*/  DW_AT_location ; 
 int DW_TAG_formal_parameter ; 
 int DW_TAG_variable ; 
 scalar_t__ die_compare_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __die_find_variable_cb(Dwarf_Die *die_mem, void *data)
{
	struct __find_variable_param *fvp = data;
	Dwarf_Attribute attr;
	int tag;

	tag = dwarf_tag(die_mem);
	if ((tag == DW_TAG_formal_parameter ||
	     tag == DW_TAG_variable) &&
	    die_compare_name(die_mem, fvp->name) &&
	/* Does the DIE have location information or external instance? */
	    (dwarf_attr(die_mem, DW_AT_external, &attr) ||
	     dwarf_attr(die_mem, DW_AT_location, &attr)))
		return DIE_FIND_CB_END;
	if (dwarf_haspc(die_mem, fvp->addr))
		return DIE_FIND_CB_CONTINUE;
	else
		return DIE_FIND_CB_SIBLING;
}