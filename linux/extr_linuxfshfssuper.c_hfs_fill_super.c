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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_op; struct hfs_sb_info* s_fs_info; } ;
struct inode {int dummy; } ;
struct hfs_sb_info {int /*<<< orphan*/  bitmap_lock; int /*<<< orphan*/  mdb_work; int /*<<< orphan*/  work_lock; struct super_block* sb; } ;
struct hfs_find_data {int entrylength; TYPE_1__* search_key; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; } ;
typedef  int /*<<< orphan*/  rec ;
typedef  int /*<<< orphan*/  hfs_cat_rec ;
struct TYPE_4__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFS_ROOT_CNID ; 
 TYPE_2__* HFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_NODIRATIME ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  flush_mdb ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int hfs_cat_find_brec (struct super_block*,int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_dentry_operations ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 struct inode* hfs_iget (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hfs_mdb_get (struct super_block*) ; 
 int /*<<< orphan*/  hfs_mdb_name (struct super_block*) ; 
 int /*<<< orphan*/  hfs_mdb_put (struct super_block*) ; 
 int /*<<< orphan*/  hfs_super_operations ; 
 int /*<<< orphan*/  hfs_xattr_handlers ; 
 struct hfs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_options (char*,struct hfs_sb_info*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct hfs_sb_info *sbi;
	struct hfs_find_data fd;
	hfs_cat_rec rec;
	struct inode *root_inode;
	int res;

	sbi = kzalloc(sizeof(struct hfs_sb_info), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sbi->sb = sb;
	sb->s_fs_info = sbi;
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->mdb_work, flush_mdb);

	res = -EINVAL;
	if (!parse_options((char *)data, sbi)) {
		pr_err("unable to parse mount options\n");
		goto bail;
	}

	sb->s_op = &hfs_super_operations;
	sb->s_xattr = hfs_xattr_handlers;
	sb->s_flags |= SB_NODIRATIME;
	mutex_init(&sbi->bitmap_lock);

	res = hfs_mdb_get(sb);
	if (res) {
		if (!silent)
			pr_warn("can't find a HFS filesystem on dev %s\n",
				hfs_mdb_name(sb));
		res = -EINVAL;
		goto bail;
	}

	/* try to get the root inode */
	res = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	if (res)
		goto bail_no_root;
	res = hfs_cat_find_brec(sb, HFS_ROOT_CNID, &fd);
	if (!res) {
		if (fd.entrylength > sizeof(rec) || fd.entrylength < 0) {
			res =  -EIO;
			goto bail;
		}
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset, fd.entrylength);
	}
	if (res) {
		hfs_find_exit(&fd);
		goto bail_no_root;
	}
	res = -EINVAL;
	root_inode = hfs_iget(sb, &fd.search_key->cat, &rec);
	hfs_find_exit(&fd);
	if (!root_inode)
		goto bail_no_root;

	sb->s_d_op = &hfs_dentry_operations;
	res = -ENOMEM;
	sb->s_root = d_make_root(root_inode);
	if (!sb->s_root)
		goto bail_no_root;

	/* everything's okay */
	return 0;

bail_no_root:
	pr_err("get root inode failed\n");
bail:
	hfs_mdb_put(sb);
	return res;
}