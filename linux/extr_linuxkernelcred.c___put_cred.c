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
struct cred {int /*<<< orphan*/  rcu; int /*<<< orphan*/  usage; } ;
struct TYPE_2__ {struct cred* real_cred; struct cred* cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kdebug (char*,struct cred*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred_rcu ; 
 int /*<<< orphan*/  read_cred_subscribers (struct cred*) ; 

void __put_cred(struct cred *cred)
{
	kdebug("__put_cred(%p{%d,%d})", cred,
	       atomic_read(&cred->usage),
	       read_cred_subscribers(cred));

	BUG_ON(atomic_read(&cred->usage) != 0);
#ifdef CONFIG_DEBUG_CREDENTIALS
	BUG_ON(read_cred_subscribers(cred) != 0);
	cred->magic = CRED_MAGIC_DEAD;
	cred->put_addr = __builtin_return_address(0);
#endif
	BUG_ON(cred == current->cred);
	BUG_ON(cred == current->real_cred);

	call_rcu(&cred->rcu, put_cred_rcu);
}