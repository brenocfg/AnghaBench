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
struct kern_ipc_perm {int dummy; } ;
struct ipc_ids {int /*<<< orphan*/  ipcs_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct kern_ipc_perm* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct kern_ipc_perm* idr_find (int /*<<< orphan*/ *,int) ; 
 int ipcid_to_idx (int) ; 

struct kern_ipc_perm *ipc_obtain_object_idr(struct ipc_ids *ids, int id)
{
	struct kern_ipc_perm *out;
	int idx = ipcid_to_idx(id);

	out = idr_find(&ids->ipcs_idr, idx);
	if (!out)
		return ERR_PTR(-EINVAL);

	return out;
}