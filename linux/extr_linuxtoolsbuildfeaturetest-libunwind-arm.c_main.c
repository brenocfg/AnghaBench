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
typedef  scalar_t__ unw_addr_space_t ;

/* Variables and functions */
 int /*<<< orphan*/  accessors ; 
 int /*<<< orphan*/  dwarf_search_unwind_table (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unw_create_addr_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unw_init_remote (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

int main(void)
{
	unw_addr_space_t addr_space;

	addr_space = unw_create_addr_space(&accessors, 0);
	if (addr_space)
		return 0;

	unw_init_remote(NULL, addr_space, NULL);
	dwarf_search_unwind_table(addr_space, 0, NULL, NULL, 0, NULL);

	return 0;
}