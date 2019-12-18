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
typedef  scalar_t__ Dwarf_Word ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_call_line ; 
 int ENOENT ; 
 int /*<<< orphan*/  dwarf_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_formudata (int /*<<< orphan*/ *,scalar_t__*) ; 

int die_get_call_lineno(Dwarf_Die *in_die)
{
	Dwarf_Attribute attr;
	Dwarf_Word ret;

	if (!dwarf_attr(in_die, DW_AT_call_line, &attr))
		return -ENOENT;

	dwarf_formudata(&attr, &ret);
	return (int)ret;
}