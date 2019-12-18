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
struct kern_ipc_perm {int deleted; int /*<<< orphan*/  id; } ;
struct ipc_ids {int max_idx; int /*<<< orphan*/  ipcs_idr; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ipc_kht_remove (struct ipc_ids*,struct kern_ipc_perm*) ; 
 int ipcid_to_idx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void ipc_rmid(struct ipc_ids *ids, struct kern_ipc_perm *ipcp)
{
	int idx = ipcid_to_idx(ipcp->id);

	idr_remove(&ids->ipcs_idr, idx);
	ipc_kht_remove(ids, ipcp);
	ids->in_use--;
	ipcp->deleted = true;

	if (unlikely(idx == ids->max_idx)) {
		do {
			idx--;
			if (idx == -1)
				break;
		} while (!idr_find(&ids->ipcs_idr, idx));
		ids->max_idx = idx;
	}
}