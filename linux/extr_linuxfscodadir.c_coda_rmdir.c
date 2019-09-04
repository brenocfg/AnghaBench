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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_dir_drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  coda_dir_update_mtime (struct inode*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int venus_rmdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int coda_rmdir(struct inode *dir, struct dentry *de)
{
	const char *name = de->d_name.name;
	int len = de->d_name.len;
	int error;

	error = venus_rmdir(dir->i_sb, coda_i2f(dir), name, len);
	if (!error) {
		/* VFS may delete the child */
		if (d_really_is_positive(de))
			clear_nlink(d_inode(de));

		/* fix the link count of the parent */
		coda_dir_drop_nlink(dir);
		coda_dir_update_mtime(dir);
	}
	return error;
}