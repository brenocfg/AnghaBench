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
struct kstatfs {int /*<<< orphan*/  f_fsid; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __kernel_fsid_t ;

/* Variables and functions */
 int statfs_by_dentry (struct dentry*,struct kstatfs*) ; 

int vfs_get_fsid(struct dentry *dentry, __kernel_fsid_t *fsid)
{
	struct kstatfs st;
	int error;

	error = statfs_by_dentry(dentry, &st);
	if (error)
		return error;

	*fsid = st.f_fsid;
	return 0;
}