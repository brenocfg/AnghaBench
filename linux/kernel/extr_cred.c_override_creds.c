#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cred {int /*<<< orphan*/  usage; } ;
struct TYPE_2__ {struct cred* cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  alter_cred_subscribers (struct cred const*,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_new_cred (struct cred*) ; 
 int /*<<< orphan*/  kdebug (char*,struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct cred*,struct cred const*) ; 
 int /*<<< orphan*/  read_cred_subscribers (struct cred const*) ; 
 int /*<<< orphan*/  validate_creds (struct cred const*) ; 

const struct cred *override_creds(const struct cred *new)
{
	const struct cred *old = current->cred;

	kdebug("override_creds(%p{%d,%d})", new,
	       atomic_read(&new->usage),
	       read_cred_subscribers(new));

	validate_creds(old);
	validate_creds(new);

	/*
	 * NOTE! This uses 'get_new_cred()' rather than 'get_cred()'.
	 *
	 * That means that we do not clear the 'non_rcu' flag, since
	 * we are only installing the cred into the thread-synchronous
	 * '->cred' pointer, not the '->real_cred' pointer that is
	 * visible to other threads under RCU.
	 *
	 * Also note that we did validate_creds() manually, not depending
	 * on the validation in 'get_cred()'.
	 */
	get_new_cred((struct cred *)new);
	alter_cred_subscribers(new, 1);
	rcu_assign_pointer(current->cred, new);
	alter_cred_subscribers(old, -1);

	kdebug("override_creds() = %p{%d,%d}", old,
	       atomic_read(&old->usage),
	       read_cred_subscribers(old));
	return old;
}