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
typedef  struct kern_ipc_perm kern_ipc_perm ;
struct ipc_namespace {int dummy; } ;
struct ipc_ids {int in_use; int /*<<< orphan*/  rwsem; int /*<<< orphan*/  ipcs_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct kern_ipc_perm* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipc_lock_object (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void free_ipcs(struct ipc_namespace *ns, struct ipc_ids *ids,
	       void (*free)(struct ipc_namespace *, struct kern_ipc_perm *))
{
	struct kern_ipc_perm *perm;
	int next_id;
	int total, in_use;

	down_write(&ids->rwsem);

	in_use = ids->in_use;

	for (total = 0, next_id = 0; total < in_use; next_id++) {
		perm = idr_find(&ids->ipcs_idr, next_id);
		if (perm == NULL)
			continue;
		rcu_read_lock();
		ipc_lock_object(perm);
		free(ns, perm);
		total++;
	}
	up_write(&ids->rwsem);
}