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
struct kmemleak_object {int /*<<< orphan*/  trace_len; int /*<<< orphan*/  trace; int /*<<< orphan*/  checksum; int /*<<< orphan*/  flags; int /*<<< orphan*/  count; int /*<<< orphan*/  min_count; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; int /*<<< orphan*/  size; int /*<<< orphan*/  pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 int /*<<< orphan*/  stack_trace_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dump_object_info(struct kmemleak_object *object)
{
	pr_notice("Object 0x%08lx (size %zu):\n",
		  object->pointer, object->size);
	pr_notice("  comm \"%s\", pid %d, jiffies %lu\n",
		  object->comm, object->pid, object->jiffies);
	pr_notice("  min_count = %d\n", object->min_count);
	pr_notice("  count = %d\n", object->count);
	pr_notice("  flags = 0x%x\n", object->flags);
	pr_notice("  checksum = %u\n", object->checksum);
	pr_notice("  backtrace:\n");
	stack_trace_print(object->trace, object->trace_len, 4);
}