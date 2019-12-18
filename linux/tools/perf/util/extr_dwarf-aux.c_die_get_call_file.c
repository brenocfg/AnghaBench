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
typedef  int /*<<< orphan*/  Dwarf_Files ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int die_get_call_fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf_diecu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* dwarf_filesrc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_getsrcfiles (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

const char *die_get_call_file(Dwarf_Die *in_die)
{
	Dwarf_Die cu_die;
	Dwarf_Files *files;
	int idx;

	idx = die_get_call_fileno(in_die);
	if (idx < 0 || !dwarf_diecu(in_die, &cu_die, NULL, NULL) ||
	    dwarf_getsrcfiles(&cu_die, &files, NULL) != 0)
		return NULL;

	return dwarf_filesrc(files, idx, NULL, NULL);
}