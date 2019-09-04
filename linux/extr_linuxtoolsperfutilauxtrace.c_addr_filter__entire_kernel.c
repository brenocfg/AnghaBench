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
struct sym_args {int started; int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct addr_filter {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_entire_kern_cb ; 
 int kallsyms__parse (char*,struct sym_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int addr_filter__entire_kernel(struct addr_filter *filt)
{
	struct sym_args args = { .started = false };
	int err;

	err = kallsyms__parse("/proc/kallsyms", &args, find_entire_kern_cb);
	if (err < 0 || !args.started) {
		pr_err("Failed to parse /proc/kallsyms\n");
		return err;
	}

	filt->addr = args.start;
	filt->size = args.size;

	return 0;
}