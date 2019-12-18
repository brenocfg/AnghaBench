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
struct kgdb_io {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct kgdb_io* dbg_io_ops ; 
 int /*<<< orphan*/  kgdb_connected ; 
 int /*<<< orphan*/  kgdb_registration_lock ; 
 int /*<<< orphan*/  kgdb_unregister_callbacks () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kgdb_unregister_io_module(struct kgdb_io *old_dbg_io_ops)
{
	BUG_ON(kgdb_connected);

	/*
	 * KGDB is no longer able to communicate out, so
	 * unregister our callbacks and reset state.
	 */
	kgdb_unregister_callbacks();

	spin_lock(&kgdb_registration_lock);

	WARN_ON_ONCE(dbg_io_ops != old_dbg_io_ops);
	dbg_io_ops = NULL;

	spin_unlock(&kgdb_registration_lock);

	pr_info("Unregistered I/O driver %s, debugger disabled\n",
		old_dbg_io_ops->name);
}