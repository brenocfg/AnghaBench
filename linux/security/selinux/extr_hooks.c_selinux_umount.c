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
struct vfsmount {int /*<<< orphan*/  mnt_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM__UNMOUNT ; 
 struct cred* current_cred () ; 
 int superblock_has_perm (struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_umount(struct vfsmount *mnt, int flags)
{
	const struct cred *cred = current_cred();

	return superblock_has_perm(cred, mnt->mnt_sb,
				   FILESYSTEM__UNMOUNT, NULL);
}