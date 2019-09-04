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
 int CODA_MAXPATHLEN ; 
 int ENAMETOOLONG ; 
 int EPERM ; 
 int /*<<< orphan*/  coda_dir_update_mtime (struct inode*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 scalar_t__ coda_iscontrol (char const*,int) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 scalar_t__ is_root_inode (struct inode*) ; 
 int strlen (char const*) ; 
 int venus_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char const*,int) ; 

__attribute__((used)) static int coda_symlink(struct inode *dir_inode, struct dentry *de,
			const char *symname)
{
	const char *name = de->d_name.name;
	int len = de->d_name.len;
	int symlen;
	int error;

	if (is_root_inode(dir_inode) && coda_iscontrol(name, len))
		return -EPERM;

	symlen = strlen(symname);
	if (symlen > CODA_MAXPATHLEN)
		return -ENAMETOOLONG;

	/*
	 * This entry is now negative. Since we do not create
	 * an inode for the entry we have to drop it.
	 */
	d_drop(de);
	error = venus_symlink(dir_inode->i_sb, coda_i2f(dir_inode), name, len,
			      symname, symlen);

	/* mtime is no good anymore */
	if (!error)
		coda_dir_update_mtime(dir_inode);

	return error;
}