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
typedef  int /*<<< orphan*/  Dwarf_Lines ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  die_get_postprologue_addr (unsigned long,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_search_idx (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ dwarf_getsrclines (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ dwarf_highpc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void die_skip_prologue(Dwarf_Die *sp_die, Dwarf_Die *cu_die,
		       Dwarf_Addr *entrypc)
{
	size_t nr_lines = 0;
	unsigned long entrypc_idx = 0;
	Dwarf_Lines *lines = NULL;
	Dwarf_Addr postprologue_addr;
	Dwarf_Addr highpc;

	if (dwarf_highpc(sp_die, &highpc))
		return;

	if (dwarf_getsrclines(cu_die, &lines, &nr_lines))
		return;

	if (!die_search_idx(lines, nr_lines, *entrypc, &entrypc_idx))
		return;

	if (!die_get_postprologue_addr(entrypc_idx, lines, nr_lines,
				       highpc, &postprologue_addr))
		return;

	*entrypc = postprologue_addr;
}