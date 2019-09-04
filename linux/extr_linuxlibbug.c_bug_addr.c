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
struct bug_entry {unsigned long bug_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long bug_addr(const struct bug_entry *bug)
{
#ifndef CONFIG_GENERIC_BUG_RELATIVE_POINTERS
	return bug->bug_addr;
#else
	return (unsigned long)bug + bug->bug_addr_disp;
#endif
}