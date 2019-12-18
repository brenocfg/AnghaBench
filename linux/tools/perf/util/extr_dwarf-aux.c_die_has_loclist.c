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
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_location ; 
 scalar_t__ DW_FORM_sec_offset ; 
 int DW_TAG_formal_parameter ; 
 int DW_TAG_variable ; 
 scalar_t__ dwarf_attr_integrate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dwarf_tag (int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_whatform (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool die_has_loclist(Dwarf_Die *vr_die)
{
	Dwarf_Attribute loc;
	int tag = dwarf_tag(vr_die);

	if (tag != DW_TAG_formal_parameter &&
	    tag != DW_TAG_variable)
		return false;

	return (dwarf_attr_integrate(vr_die, DW_AT_location, &loc) &&
		dwarf_whatform(&loc) == DW_FORM_sec_offset);
}