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
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  __die_find_inline_cb ; 
 int /*<<< orphan*/ * die_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * die_find_realfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cu_walk_functions_at(Dwarf_Die *cu_die, Dwarf_Addr addr,
		    int (*callback)(Dwarf_Die *, void *), void *data)
{
	Dwarf_Die die_mem;
	Dwarf_Die *sc_die;
	int ret = -ENOENT;

	/* Inlined function could be recursive. Trace it until fail */
	for (sc_die = die_find_realfunc(cu_die, addr, &die_mem);
	     sc_die != NULL;
	     sc_die = die_find_child(sc_die, __die_find_inline_cb, &addr,
				     &die_mem)) {
		ret = callback(sc_die, data);
		if (ret)
			break;
	}

	return ret;

}