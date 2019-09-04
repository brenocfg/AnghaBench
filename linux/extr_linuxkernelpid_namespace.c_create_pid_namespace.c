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
struct user_namespace {int dummy; } ;
struct ucounts {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct pid_namespace {int level; int /*<<< orphan*/  idr; int /*<<< orphan*/  proc_work; int /*<<< orphan*/  pid_allocated; struct ucounts* ucounts; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  parent; int /*<<< orphan*/  kref; TYPE_1__ ns; int /*<<< orphan*/ * pid_cachep; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct pid_namespace* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MAX_PID_NS_LEVEL ; 
 int /*<<< orphan*/  PIDNS_ADDING ; 
 int /*<<< orphan*/ * create_pid_cachep (unsigned int) ; 
 int /*<<< orphan*/  dec_pid_namespaces (struct ucounts*) ; 
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  get_user_ns (struct user_namespace*) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_userns (int /*<<< orphan*/ ,struct user_namespace*) ; 
 struct ucounts* inc_pid_namespaces (struct user_namespace*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pid_namespace*) ; 
 struct pid_namespace* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int ns_alloc_inum (TYPE_1__*) ; 
 int /*<<< orphan*/  pid_ns_cachep ; 
 int /*<<< orphan*/  pidns_operations ; 
 int /*<<< orphan*/  proc_cleanup_work ; 

__attribute__((used)) static struct pid_namespace *create_pid_namespace(struct user_namespace *user_ns,
	struct pid_namespace *parent_pid_ns)
{
	struct pid_namespace *ns;
	unsigned int level = parent_pid_ns->level + 1;
	struct ucounts *ucounts;
	int err;

	err = -EINVAL;
	if (!in_userns(parent_pid_ns->user_ns, user_ns))
		goto out;

	err = -ENOSPC;
	if (level > MAX_PID_NS_LEVEL)
		goto out;
	ucounts = inc_pid_namespaces(user_ns);
	if (!ucounts)
		goto out;

	err = -ENOMEM;
	ns = kmem_cache_zalloc(pid_ns_cachep, GFP_KERNEL);
	if (ns == NULL)
		goto out_dec;

	idr_init(&ns->idr);

	ns->pid_cachep = create_pid_cachep(level);
	if (ns->pid_cachep == NULL)
		goto out_free_idr;

	err = ns_alloc_inum(&ns->ns);
	if (err)
		goto out_free_idr;
	ns->ns.ops = &pidns_operations;

	kref_init(&ns->kref);
	ns->level = level;
	ns->parent = get_pid_ns(parent_pid_ns);
	ns->user_ns = get_user_ns(user_ns);
	ns->ucounts = ucounts;
	ns->pid_allocated = PIDNS_ADDING;
	INIT_WORK(&ns->proc_work, proc_cleanup_work);

	return ns;

out_free_idr:
	idr_destroy(&ns->idr);
	kmem_cache_free(pid_ns_cachep, ns);
out_dec:
	dec_pid_namespaces(ucounts);
out:
	return ERR_PTR(err);
}