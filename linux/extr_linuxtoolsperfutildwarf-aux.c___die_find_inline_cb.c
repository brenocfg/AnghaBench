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
 int DIE_FIND_CB_CONTINUE ; 
 int DIE_FIND_CB_END ; 
 scalar_t__ DW_TAG_inlined_subroutine ; 
 scalar_t__ dwarf_haspc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dwarf_tag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __die_find_inline_cb(Dwarf_Die *die_mem, void *data)
{
	Dwarf_Addr *addr = data;

	if (dwarf_tag(die_mem) == DW_TAG_inlined_subroutine &&
	    dwarf_haspc(die_mem, *addr))
		return DIE_FIND_CB_END;

	return DIE_FIND_CB_CONTINUE;
}