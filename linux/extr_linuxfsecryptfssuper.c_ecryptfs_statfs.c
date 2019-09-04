#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kstatfs {int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_type; } ;
struct dentry {TYPE_3__* d_sb; } ;
struct TYPE_6__ {TYPE_1__* s_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  mount_crypt_stat; } ;
struct TYPE_4__ {int (* statfs ) (struct dentry*,struct kstatfs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_SUPER_MAGIC ; 
 int ENOSYS ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int ecryptfs_set_f_namelen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* ecryptfs_superblock_to_private (TYPE_3__*) ; 
 int stub1 (struct dentry*,struct kstatfs*) ; 

__attribute__((used)) static int ecryptfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);
	int rc;

	if (!lower_dentry->d_sb->s_op->statfs)
		return -ENOSYS;

	rc = lower_dentry->d_sb->s_op->statfs(lower_dentry, buf);
	if (rc)
		return rc;

	buf->f_type = ECRYPTFS_SUPER_MAGIC;
	rc = ecryptfs_set_f_namelen(&buf->f_namelen, buf->f_namelen,
	       &ecryptfs_superblock_to_private(dentry->d_sb)->mount_crypt_stat);

	return rc;
}