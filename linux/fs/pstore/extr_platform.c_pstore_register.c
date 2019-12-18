#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pstore_info {int flags; scalar_t__ name; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  read_mutex; scalar_t__ write_user; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct module* owner; } ;
struct module {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int PSTORE_FLAGS_CONSOLE ; 
 int PSTORE_FLAGS_DMESG ; 
 int PSTORE_FLAGS_FTRACE ; 
 int PSTORE_FLAGS_PMSG ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  allocate_buf_for_compression () ; 
 scalar_t__ backend ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,...) ; 
 struct pstore_info* psinfo ; 
 int /*<<< orphan*/  pstore_get_records (int /*<<< orphan*/ ) ; 
 scalar_t__ pstore_is_mounted () ; 
 int /*<<< orphan*/  pstore_lock ; 
 int /*<<< orphan*/  pstore_register_console () ; 
 int /*<<< orphan*/  pstore_register_ftrace () ; 
 int /*<<< orphan*/  pstore_register_kmsg () ; 
 int /*<<< orphan*/  pstore_register_pmsg () ; 
 TYPE_1__ pstore_timer ; 
 scalar_t__ pstore_update_ms ; 
 scalar_t__ pstore_write_user_compat ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

int pstore_register(struct pstore_info *psi)
{
	struct module *owner = psi->owner;

	if (backend && strcmp(backend, psi->name)) {
		pr_warn("ignoring unexpected backend '%s'\n", psi->name);
		return -EPERM;
	}

	/* Sanity check flags. */
	if (!psi->flags) {
		pr_warn("backend '%s' must support at least one frontend\n",
			psi->name);
		return -EINVAL;
	}

	/* Check for required functions. */
	if (!psi->read || !psi->write) {
		pr_warn("backend '%s' must implement read() and write()\n",
			psi->name);
		return -EINVAL;
	}

	spin_lock(&pstore_lock);
	if (psinfo) {
		pr_warn("backend '%s' already loaded: ignoring '%s'\n",
			psinfo->name, psi->name);
		spin_unlock(&pstore_lock);
		return -EBUSY;
	}

	if (!psi->write_user)
		psi->write_user = pstore_write_user_compat;
	psinfo = psi;
	mutex_init(&psinfo->read_mutex);
	sema_init(&psinfo->buf_lock, 1);
	spin_unlock(&pstore_lock);

	if (owner && !try_module_get(owner)) {
		psinfo = NULL;
		return -EINVAL;
	}

	if (psi->flags & PSTORE_FLAGS_DMESG)
		allocate_buf_for_compression();

	if (pstore_is_mounted())
		pstore_get_records(0);

	if (psi->flags & PSTORE_FLAGS_DMESG)
		pstore_register_kmsg();
	if (psi->flags & PSTORE_FLAGS_CONSOLE)
		pstore_register_console();
	if (psi->flags & PSTORE_FLAGS_FTRACE)
		pstore_register_ftrace();
	if (psi->flags & PSTORE_FLAGS_PMSG)
		pstore_register_pmsg();

	/* Start watching for new records, if desired. */
	if (pstore_update_ms >= 0) {
		pstore_timer.expires = jiffies +
			msecs_to_jiffies(pstore_update_ms);
		add_timer(&pstore_timer);
	}

	/*
	 * Update the module parameter backend, so it is visible
	 * through /sys/module/pstore/parameters/backend
	 */
	backend = psi->name;

	pr_info("Registered %s as persistent store backend\n", psi->name);

	module_put(owner);

	return 0;
}