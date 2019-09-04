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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int sym_not_found_error(const char *sym_name, int idx)
{
	if (idx > 0) {
		pr_err("N'th occurrence (N=%d) of symbol '%s' not found.\n",
		       idx, sym_name);
	} else if (!idx) {
		pr_err("Global symbol '%s' not found.\n", sym_name);
	} else {
		pr_err("Symbol '%s' not found.\n", sym_name);
	}
	pr_err("Note that symbols must be functions.\n");

	return -EINVAL;
}