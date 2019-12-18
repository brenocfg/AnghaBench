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
struct bug_entry {int dummy; } ;

/* Variables and functions */
 struct bug_entry* __start___bug_table ; 
 struct bug_entry* __stop___bug_table ; 
 unsigned long bug_addr (struct bug_entry*) ; 
 struct bug_entry* module_find_bug (unsigned long) ; 

struct bug_entry *find_bug(unsigned long bugaddr)
{
	struct bug_entry *bug;

	for (bug = __start___bug_table; bug < __stop___bug_table; ++bug)
		if (bugaddr == bug_addr(bug))
			return bug;

	return module_find_bug(bugaddr);
}