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
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int DIE_FIND_CB_END ; 
 int DIE_FIND_CB_SIBLING ; 
 scalar_t__ DW_TAG_member ; 
 scalar_t__ die_compare_name (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ die_find_member (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ die_get_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diename (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __die_find_member_cb(Dwarf_Die *die_mem, void *data)
{
	const char *name = data;

	if (dwarf_tag(die_mem) == DW_TAG_member) {
		if (die_compare_name(die_mem, name))
			return DIE_FIND_CB_END;
		else if (!dwarf_diename(die_mem)) {	/* Unnamed structure */
			Dwarf_Die type_die, tmp_die;
			if (die_get_type(die_mem, &type_die) &&
			    die_find_member(&type_die, name, &tmp_die))
				return DIE_FIND_CB_END;
		}
	}
	return DIE_FIND_CB_SIBLING;
}