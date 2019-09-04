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
 int /*<<< orphan*/  DW_AT_linkage_name ; 
 int /*<<< orphan*/ * dwarf_attr_integrate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* dwarf_formstring (int /*<<< orphan*/ *) ; 

const char *die_get_linkage_name(Dwarf_Die *dw_die)
{
	Dwarf_Attribute attr;

	if (dwarf_attr_integrate(dw_die, DW_AT_linkage_name, &attr) == NULL)
		return NULL;
	return dwarf_formstring(&attr);
}