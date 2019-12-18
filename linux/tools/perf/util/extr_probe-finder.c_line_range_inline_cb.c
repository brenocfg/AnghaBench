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
 int find_line_range_by_line (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int line_range_inline_cb(Dwarf_Die *in_die, void *data)
{
	int ret = find_line_range_by_line(in_die, data);

	/*
	 * We have to check all instances of inlined function, because
	 * some execution paths can be optimized out depends on the
	 * function argument of instances. However, if an error occurs,
	 * it should be handled by the caller.
	 */
	return ret < 0 ? ret : 0;
}