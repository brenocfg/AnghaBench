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
struct user_namespace {int dummy; } ;
struct ucounts {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ops; } ;
struct ipc_namespace {TYPE_1__ ns; int /*<<< orphan*/  user_ns; struct ucounts* ucounts; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 struct ipc_namespace* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dec_ipc_namespaces (struct ucounts*) ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 struct ucounts* inc_ipc_namespaces (struct user_namespace*) ; 
 int /*<<< orphan*/  ipcns_operations ; 
 int /*<<< orphan*/  kfree (struct ipc_namespace*) ; 
 struct ipc_namespace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mq_init_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  msg_init_ns (struct ipc_namespace*) ; 
 int ns_alloc_inum (TYPE_1__*) ; 
 int /*<<< orphan*/  ns_free_inum (TYPE_1__*) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sem_init_ns (struct ipc_namespace*) ; 
 int /*<<< orphan*/  shm_init_ns (struct ipc_namespace*) ; 

__attribute__((used)) static struct ipc_namespace *create_ipc_ns(struct user_namespace *user_ns,
					   struct ipc_namespace *old_ns)
{
	struct ipc_namespace *ns;
	struct ucounts *ucounts;
	int err;

	err = -ENOSPC;
	ucounts = inc_ipc_namespaces(user_ns);
	if (!ucounts)
		goto fail;

	err = -ENOMEM;
	ns = kzalloc(sizeof(struct ipc_namespace), GFP_KERNEL);
	if (ns == NULL)
		goto fail_dec;

	err = ns_alloc_inum(&ns->ns);
	if (err)
		goto fail_free;
	ns->ns.ops = &ipcns_operations;

	refcount_set(&ns->count, 1);
	ns->user_ns = get_user_ns(user_ns);
	ns->ucounts = ucounts;

	err = mq_init_ns(ns);
	if (err)
		goto fail_put;

	sem_init_ns(ns);
	msg_init_ns(ns);
	shm_init_ns(ns);

	return ns;

fail_put:
	put_user_ns(ns->user_ns);
	ns_free_inum(&ns->ns);
fail_free:
	kfree(ns);
fail_dec:
	dec_ipc_namespaces(ucounts);
fail:
	return ERR_PTR(err);
}