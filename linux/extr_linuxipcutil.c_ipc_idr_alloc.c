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
struct kern_ipc_perm {int seq; int id; } ;
struct ipc_ids {scalar_t__ seq; int /*<<< orphan*/  ipcs_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ IPCID_SEQ_MAX ; 
 int SEQ_MULTIPLIER ; 
 int idr_alloc (int /*<<< orphan*/ *,struct kern_ipc_perm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcid_to_idx (int) ; 
 int ipcid_to_seqx (int) ; 

__attribute__((used)) static inline int ipc_idr_alloc(struct ipc_ids *ids, struct kern_ipc_perm *new)
{
	int idx, next_id = -1;

#ifdef CONFIG_CHECKPOINT_RESTORE
	next_id = ids->next_id;
	ids->next_id = -1;
#endif

	/*
	 * As soon as a new object is inserted into the idr,
	 * ipc_obtain_object_idr() or ipc_obtain_object_check() can find it,
	 * and the lockless preparations for ipc operations can start.
	 * This means especially: permission checks, audit calls, allocation
	 * of undo structures, ...
	 *
	 * Thus the object must be fully initialized, and if something fails,
	 * then the full tear-down sequence must be followed.
	 * (i.e.: set new->deleted, reduce refcount, call_rcu())
	 */

	if (next_id < 0) { /* !CHECKPOINT_RESTORE or next_id is unset */
		new->seq = ids->seq++;
		if (ids->seq > IPCID_SEQ_MAX)
			ids->seq = 0;
		idx = idr_alloc(&ids->ipcs_idr, new, 0, 0, GFP_NOWAIT);
	} else {
		new->seq = ipcid_to_seqx(next_id);
		idx = idr_alloc(&ids->ipcs_idr, new, ipcid_to_idx(next_id),
				0, GFP_NOWAIT);
	}
	if (idx >= 0)
		new->id = SEQ_MULTIPLIER * new->seq + idx;
	return idx;
}