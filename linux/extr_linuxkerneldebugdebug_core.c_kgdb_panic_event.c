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
 int NOTIFY_DONE ; 
 scalar_t__ dbg_kdb_mode ; 
 int /*<<< orphan*/  kdb_printf (char*,char*) ; 
 int /*<<< orphan*/  kgdb_breakpoint () ; 
 scalar_t__ panic_timeout ; 

__attribute__((used)) static int kgdb_panic_event(struct notifier_block *self,
			    unsigned long val,
			    void *data)
{
	/*
	 * Avoid entering the debugger if we were triggered due to a panic
	 * We don't want to get stuck waiting for input from user in such case.
	 * panic_timeout indicates the system should automatically
	 * reboot on panic.
	 */
	if (panic_timeout)
		return NOTIFY_DONE;

	if (dbg_kdb_mode)
		kdb_printf("PANIC: %s\n", (char *)data);
	kgdb_breakpoint();
	return NOTIFY_DONE;
}