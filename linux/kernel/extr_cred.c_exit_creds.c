#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* cred; int /*<<< orphan*/ * real_cred; int /*<<< orphan*/  pid; } ;
struct cred {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cached_requested_key; } ;
struct TYPE_4__ {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  alter_cred_subscribers (struct cred*,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  kdebug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  read_cred_subscribers (TYPE_1__*) ; 
 int /*<<< orphan*/  validate_creds (struct cred*) ; 

void exit_creds(struct task_struct *tsk)
{
	struct cred *cred;

	kdebug("exit_creds(%u,%p,%p,{%d,%d})", tsk->pid, tsk->real_cred, tsk->cred,
	       atomic_read(&tsk->cred->usage),
	       read_cred_subscribers(tsk->cred));

	cred = (struct cred *) tsk->real_cred;
	tsk->real_cred = NULL;
	validate_creds(cred);
	alter_cred_subscribers(cred, -1);
	put_cred(cred);

	cred = (struct cred *) tsk->cred;
	tsk->cred = NULL;
	validate_creds(cred);
	alter_cred_subscribers(cred, -1);
	put_cred(cred);

#ifdef CONFIG_KEYS_REQUEST_CACHE
	key_put(current->cached_requested_key);
	current->cached_requested_key = NULL;
#endif
}