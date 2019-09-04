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
 int /*<<< orphan*/  kdebug (char*,struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct cred*,struct cred const*) ; 
 int /*<<< orphan*/  read_cred_subscribers (struct cred const*) ; 
 int /*<<< orphan*/  validate_creds (struct cred const*) ; 

void revert_creds(const struct cred *old)
{
	const struct cred *override = current->cred;

	kdebug("revert_creds(%p{%d,%d})", old,
	       atomic_read(&old->usage),
	       read_cred_subscribers(old));

	validate_creds(old);
	validate_creds(override);
	alter_cred_subscribers(old, 1);
	rcu_assign_pointer(current->cred, old);
	alter_cred_subscribers(override, -1);
	put_cred(override);
}