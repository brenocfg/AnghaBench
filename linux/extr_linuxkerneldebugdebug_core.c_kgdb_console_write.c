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
struct console {int dummy; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ dbg_kdb_mode ; 
 int /*<<< orphan*/  gdbstub_msg_write (char const*,unsigned int) ; 
 int /*<<< orphan*/  kgdb_active ; 
 int /*<<< orphan*/  kgdb_connected ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void kgdb_console_write(struct console *co, const char *s,
   unsigned count)
{
	unsigned long flags;

	/* If we're debugging, or KGDB has not connected, don't try
	 * and print. */
	if (!kgdb_connected || atomic_read(&kgdb_active) != -1 || dbg_kdb_mode)
		return;

	local_irq_save(flags);
	gdbstub_msg_write(s, count);
	local_irq_restore(flags);
}