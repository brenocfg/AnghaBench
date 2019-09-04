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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int is_subdir (struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_acceptable(void *ctx, struct dentry *dentry)
{
	/*
	 * A non-dir origin may be disconnected, which is fine, because
	 * we only need it for its unique inode number.
	 */
	if (!d_is_dir(dentry))
		return 1;

	/* Don't decode a deleted empty directory */
	if (d_unhashed(dentry))
		return 0;

	/* Check if directory belongs to the layer we are decoding from */
	return is_subdir(dentry, ((struct vfsmount *)ctx)->mnt_root);
}