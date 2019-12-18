#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hfs_iget_data {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct hfs_find_data {TYPE_2__* search_key; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  rec ;
typedef  int /*<<< orphan*/  hfs_cat_rec ;
struct TYPE_8__ {struct inode* rsrc_inode; int /*<<< orphan*/  cat_key; } ;
struct TYPE_7__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_6__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 TYPE_4__* HFS_I (struct inode*) ; 
 scalar_t__ HFS_IS_RSRC (struct inode*) ; 
 TYPE_3__* HFS_SB (int /*<<< orphan*/ ) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  dont_mount (struct dentry*) ; 
 int hfs_brec_read (struct hfs_find_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_read_inode (struct inode*,struct hfs_iget_data*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  inode_fake_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dentry *hfs_file_lookup(struct inode *dir, struct dentry *dentry,
				      unsigned int flags)
{
	struct inode *inode = NULL;
	hfs_cat_rec rec;
	struct hfs_find_data fd;
	int res;

	if (HFS_IS_RSRC(dir) || strcmp(dentry->d_name.name, "rsrc"))
		goto out;

	inode = HFS_I(dir)->rsrc_inode;
	if (inode)
		goto out;

	inode = new_inode(dir->i_sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	res = hfs_find_init(HFS_SB(dir->i_sb)->cat_tree, &fd);
	if (res) {
		iput(inode);
		return ERR_PTR(res);
	}
	fd.search_key->cat = HFS_I(dir)->cat_key;
	res = hfs_brec_read(&fd, &rec, sizeof(rec));
	if (!res) {
		struct hfs_iget_data idata = { NULL, &rec };
		hfs_read_inode(inode, &idata);
	}
	hfs_find_exit(&fd);
	if (res) {
		iput(inode);
		return ERR_PTR(res);
	}
	HFS_I(inode)->rsrc_inode = dir;
	HFS_I(dir)->rsrc_inode = inode;
	igrab(dir);
	inode_fake_hash(inode);
	mark_inode_dirty(inode);
	dont_mount(dentry);
out:
	return d_splice_alias(inode, dentry);
}