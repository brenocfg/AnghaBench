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
struct Qdisc_ops {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct Qdisc_ops const* default_qdisc_ops ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct Qdisc_ops* qdisc_lookup_default (char const*) ; 
 int /*<<< orphan*/  qdisc_mod_lock ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int qdisc_set_default(const char *name)
{
	const struct Qdisc_ops *ops;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	write_lock(&qdisc_mod_lock);
	ops = qdisc_lookup_default(name);
	if (!ops) {
		/* Not found, drop lock and try to load module */
		write_unlock(&qdisc_mod_lock);
		request_module("sch_%s", name);
		write_lock(&qdisc_mod_lock);

		ops = qdisc_lookup_default(name);
	}

	if (ops) {
		/* Set new default */
		module_put(default_qdisc_ops->owner);
		default_qdisc_ops = ops;
	}
	write_unlock(&qdisc_mod_lock);

	return ops ? 0 : -ENOENT;
}