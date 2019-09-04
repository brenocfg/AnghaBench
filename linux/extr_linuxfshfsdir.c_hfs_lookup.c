#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  d_name; int /*<<< orphan*/  i_ino; } ;
struct hfs_find_data {TYPE_1__* search_key; } ;
struct dentry {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  d_name; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  rec ;
typedef  int /*<<< orphan*/  hfs_cat_rec ;
struct TYPE_4__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 struct inode* ERR_PTR (int) ; 
 TYPE_2__* HFS_SB (int /*<<< orphan*/ ) ; 
 struct inode* d_splice_alias (struct inode*,struct inode*) ; 
 int hfs_brec_read (struct hfs_find_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hfs_cat_build_key (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 struct inode* hfs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *hfs_lookup(struct inode *dir, struct dentry *dentry,
				 unsigned int flags)
{
	hfs_cat_rec rec;
	struct hfs_find_data fd;
	struct inode *inode = NULL;
	int res;

	res = hfs_find_init(HFS_SB(dir->i_sb)->cat_tree, &fd);
	if (res)
		return ERR_PTR(res);
	hfs_cat_build_key(dir->i_sb, fd.search_key, dir->i_ino, &dentry->d_name);
	res = hfs_brec_read(&fd, &rec, sizeof(rec));
	if (res) {
		if (res != -ENOENT)
			inode = ERR_PTR(res);
	} else {
		inode = hfs_iget(dir->i_sb, &fd.search_key->cat, &rec);
		if (!inode)
			inode = ERR_PTR(-EACCES);
	}
	hfs_find_exit(&fd);
	return d_splice_alias(inode, dentry);
}