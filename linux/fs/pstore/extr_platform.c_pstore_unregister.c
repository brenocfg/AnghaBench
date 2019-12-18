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
struct pstore_info {int flags; } ;

/* Variables and functions */
 int PSTORE_FLAGS_CONSOLE ; 
 int PSTORE_FLAGS_DMESG ; 
 int PSTORE_FLAGS_FTRACE ; 
 int PSTORE_FLAGS_PMSG ; 
 int /*<<< orphan*/ * backend ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_buf_for_compression () ; 
 int /*<<< orphan*/ * psinfo ; 
 int /*<<< orphan*/  pstore_timer ; 
 int /*<<< orphan*/  pstore_unregister_console () ; 
 int /*<<< orphan*/  pstore_unregister_ftrace () ; 
 int /*<<< orphan*/  pstore_unregister_kmsg () ; 
 int /*<<< orphan*/  pstore_unregister_pmsg () ; 
 int pstore_update_ms ; 
 int /*<<< orphan*/  pstore_work ; 

void pstore_unregister(struct pstore_info *psi)
{
	/* Stop timer and make sure all work has finished. */
	pstore_update_ms = -1;
	del_timer_sync(&pstore_timer);
	flush_work(&pstore_work);

	if (psi->flags & PSTORE_FLAGS_PMSG)
		pstore_unregister_pmsg();
	if (psi->flags & PSTORE_FLAGS_FTRACE)
		pstore_unregister_ftrace();
	if (psi->flags & PSTORE_FLAGS_CONSOLE)
		pstore_unregister_console();
	if (psi->flags & PSTORE_FLAGS_DMESG)
		pstore_unregister_kmsg();

	free_buf_for_compression();

	psinfo = NULL;
	backend = NULL;
}