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
 int /*<<< orphan*/  C_VATTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  coda_dir_drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  coda_dir_inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  coda_dir_update_mtime (struct inode*) ; 
 int /*<<< orphan*/  coda_flag_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int venus_rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*,char const*) ; 

__attribute__((used)) static int coda_rename(struct inode *old_dir, struct dentry *old_dentry,
		       struct inode *new_dir, struct dentry *new_dentry,
		       unsigned int flags)
{
	const char *old_name = old_dentry->d_name.name;
	const char *new_name = new_dentry->d_name.name;
	int old_length = old_dentry->d_name.len;
	int new_length = new_dentry->d_name.len;
	int error;

	if (flags)
		return -EINVAL;

	error = venus_rename(old_dir->i_sb, coda_i2f(old_dir),
			     coda_i2f(new_dir), old_length, new_length,
			     (const char *) old_name, (const char *)new_name);
	if (!error) {
		if (d_really_is_positive(new_dentry)) {
			if (d_is_dir(new_dentry)) {
				coda_dir_drop_nlink(old_dir);
				coda_dir_inc_nlink(new_dir);
			}
			coda_dir_update_mtime(old_dir);
			coda_dir_update_mtime(new_dir);
			coda_flag_inode(d_inode(new_dentry), C_VATTR);
		} else {
			coda_flag_inode(old_dir, C_VATTR);
			coda_flag_inode(new_dir, C_VATTR);
		}
	}
	return error;
}