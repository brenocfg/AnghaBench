#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kstatfs {long long f_blocks; long long f_bfree; long long f_bavail; long long f_files; long long f_ffree; int /*<<< orphan*/  f_type; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_fsid; int /*<<< orphan*/  f_bsize; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTFS_SUPER_MAGIC ; 
 int do_statfs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long long*,long long*,long long*,long long*,long long*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hostfs_statfs(struct dentry *dentry, struct kstatfs *sf)
{
	/*
	 * do_statfs uses struct statfs64 internally, but the linux kernel
	 * struct statfs still has 32-bit versions for most of these fields,
	 * so we convert them here
	 */
	int err;
	long long f_blocks;
	long long f_bfree;
	long long f_bavail;
	long long f_files;
	long long f_ffree;

	err = do_statfs(dentry->d_sb->s_fs_info,
			&sf->f_bsize, &f_blocks, &f_bfree, &f_bavail, &f_files,
			&f_ffree, &sf->f_fsid, sizeof(sf->f_fsid),
			&sf->f_namelen);
	if (err)
		return err;
	sf->f_blocks = f_blocks;
	sf->f_bfree = f_bfree;
	sf->f_bavail = f_bavail;
	sf->f_files = f_files;
	sf->f_ffree = f_ffree;
	sf->f_type = HOSTFS_SUPER_MAGIC;
	return 0;
}