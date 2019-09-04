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
struct pt_regs {int dummy; } ;
struct my_data {int /*<<< orphan*/  entry_stamp; } ;
struct kretprobe_instance {scalar_t__ data; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  func_name ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long,long long) ; 
 unsigned long regs_return_value (struct pt_regs*) ; 

__attribute__((used)) static int ret_handler(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	unsigned long retval = regs_return_value(regs);
	struct my_data *data = (struct my_data *)ri->data;
	s64 delta;
	ktime_t now;

	now = ktime_get();
	delta = ktime_to_ns(ktime_sub(now, data->entry_stamp));
	pr_info("%s returned %lu and took %lld ns to execute\n",
			func_name, retval, (long long)delta);
	return 0;
}