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
 int /*<<< orphan*/  __die_find_inline_cb ; 
 int /*<<< orphan*/ * die_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Dwarf_Die *die_find_top_inlinefunc(Dwarf_Die *sp_die, Dwarf_Addr addr,
				   Dwarf_Die *die_mem)
{
	return die_find_child(sp_die, __die_find_inline_cb, &addr, die_mem);
}