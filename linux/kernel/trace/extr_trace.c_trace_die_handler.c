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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  DIE_OOPS 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ftrace_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_dump_on_oops ; 

__attribute__((used)) static int trace_die_handler(struct notifier_block *self,
			     unsigned long val,
			     void *data)
{
	switch (val) {
	case DIE_OOPS:
		if (ftrace_dump_on_oops)
			ftrace_dump(ftrace_dump_on_oops);
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}