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
struct task_struct {struct nsproxy* nsproxy; } ;
struct nsproxy {TYPE_1__* mnt_ns; } ;
struct ns_common {int dummy; } ;
struct TYPE_2__ {struct ns_common ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_mnt_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  to_mnt_ns (struct ns_common*) ; 

__attribute__((used)) static struct ns_common *mntns_get(struct task_struct *task)
{
	struct ns_common *ns = NULL;
	struct nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	if (nsproxy) {
		ns = &nsproxy->mnt_ns->ns;
		get_mnt_ns(to_mnt_ns(ns));
	}
	task_unlock(task);

	return ns;
}