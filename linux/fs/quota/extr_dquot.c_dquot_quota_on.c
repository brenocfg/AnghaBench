#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct path {TYPE_1__* dentry; } ;
struct TYPE_3__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int DQUOT_LIMITS_ENABLED ; 
 int DQUOT_USAGE_ENABLED ; 
 int EXDEV ; 
 int /*<<< orphan*/  d_inode (TYPE_1__*) ; 
 int security_quota_on (TYPE_1__*) ; 
 int vfs_load_quota_inode (int /*<<< orphan*/ ,int,int,int) ; 

int dquot_quota_on(struct super_block *sb, int type, int format_id,
		   const struct path *path)
{
	int error = security_quota_on(path->dentry);
	if (error)
		return error;
	/* Quota file not on the same filesystem? */
	if (path->dentry->d_sb != sb)
		error = -EXDEV;
	else
		error = vfs_load_quota_inode(d_inode(path->dentry), type,
					     format_id, DQUOT_USAGE_ENABLED |
					     DQUOT_LIMITS_ENABLED);
	return error;
}