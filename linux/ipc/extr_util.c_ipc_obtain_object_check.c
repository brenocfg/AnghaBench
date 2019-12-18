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
struct ipc_ids {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct kern_ipc_perm* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct kern_ipc_perm*) ; 
 scalar_t__ ipc_checkid (struct kern_ipc_perm*,int) ; 
 struct kern_ipc_perm* ipc_obtain_object_idr (struct ipc_ids*,int) ; 

struct kern_ipc_perm *ipc_obtain_object_check(struct ipc_ids *ids, int id)
{
	struct kern_ipc_perm *out = ipc_obtain_object_idr(ids, id);

	if (IS_ERR(out))
		goto out;

	if (ipc_checkid(out, id))
		return ERR_PTR(-EINVAL);
out:
	return out;
}