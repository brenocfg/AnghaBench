#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct super_block {int /*<<< orphan*/  s_root; } ;
struct qstr {char* name; int /*<<< orphan*/  len; } ;
struct inode {int /*<<< orphan*/  i_mode; struct super_block* i_sb; int /*<<< orphan*/  i_ino; } ;
struct hfsplus_cat_folder {int dummy; } ;
struct hfsplus_cat_file {int dummy; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  search_key; } ;
struct dentry {int /*<<< orphan*/ * d_fsdata; struct qstr d_name; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ fdType; scalar_t__ fdCreator; } ;
struct TYPE_12__ {scalar_t__ create_date; TYPE_3__ permissions; TYPE_2__ user_info; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_4__ file; TYPE_1__ folder; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ hfsplus_cat_entry ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_15__ {scalar_t__ create_date; int linkid; } ;
struct TYPE_14__ {struct inode* hidden_dir; int /*<<< orphan*/  cat_tree; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ HFSPLUS_FILE ; 
 scalar_t__ HFSPLUS_FOLDER ; 
 TYPE_8__* HFSPLUS_I (struct inode*) ; 
 TYPE_7__* HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFSP_HARDLINK_TYPE ; 
 int /*<<< orphan*/  HFSP_HFSPLUS_CREATOR ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int hfs_brec_read (struct hfs_find_data*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfsplus_cat_build_key (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr*) ; 
 struct inode* hfsplus_iget (struct super_block*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dentry *hfsplus_lookup(struct inode *dir, struct dentry *dentry,
				     unsigned int flags)
{
	struct inode *inode = NULL;
	struct hfs_find_data fd;
	struct super_block *sb;
	hfsplus_cat_entry entry;
	int err;
	u32 cnid, linkid = 0;
	u16 type;

	sb = dir->i_sb;

	dentry->d_fsdata = NULL;
	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &fd);
	if (err)
		return ERR_PTR(err);
	err = hfsplus_cat_build_key(sb, fd.search_key, dir->i_ino,
			&dentry->d_name);
	if (unlikely(err < 0))
		goto fail;
again:
	err = hfs_brec_read(&fd, &entry, sizeof(entry));
	if (err) {
		if (err == -ENOENT) {
			hfs_find_exit(&fd);
			/* No such entry */
			inode = NULL;
			goto out;
		}
		goto fail;
	}
	type = be16_to_cpu(entry.type);
	if (type == HFSPLUS_FOLDER) {
		if (fd.entrylength < sizeof(struct hfsplus_cat_folder)) {
			err = -EIO;
			goto fail;
		}
		cnid = be32_to_cpu(entry.folder.id);
		dentry->d_fsdata = (void *)(unsigned long)cnid;
	} else if (type == HFSPLUS_FILE) {
		if (fd.entrylength < sizeof(struct hfsplus_cat_file)) {
			err = -EIO;
			goto fail;
		}
		cnid = be32_to_cpu(entry.file.id);
		if (entry.file.user_info.fdType ==
				cpu_to_be32(HFSP_HARDLINK_TYPE) &&
				entry.file.user_info.fdCreator ==
				cpu_to_be32(HFSP_HFSPLUS_CREATOR) &&
				HFSPLUS_SB(sb)->hidden_dir &&
				(entry.file.create_date ==
					HFSPLUS_I(HFSPLUS_SB(sb)->hidden_dir)->
						create_date ||
				entry.file.create_date ==
					HFSPLUS_I(d_inode(sb->s_root))->
						create_date)) {
			struct qstr str;
			char name[32];

			if (dentry->d_fsdata) {
				/*
				 * We found a link pointing to another link,
				 * so ignore it and treat it as regular file.
				 */
				cnid = (unsigned long)dentry->d_fsdata;
				linkid = 0;
			} else {
				dentry->d_fsdata = (void *)(unsigned long)cnid;
				linkid =
					be32_to_cpu(entry.file.permissions.dev);
				str.len = sprintf(name, "iNode%d", linkid);
				str.name = name;
				err = hfsplus_cat_build_key(sb, fd.search_key,
					HFSPLUS_SB(sb)->hidden_dir->i_ino,
					&str);
				if (unlikely(err < 0))
					goto fail;
				goto again;
			}
		} else if (!dentry->d_fsdata)
			dentry->d_fsdata = (void *)(unsigned long)cnid;
	} else {
		pr_err("invalid catalog entry type in lookup\n");
		err = -EIO;
		goto fail;
	}
	hfs_find_exit(&fd);
	inode = hfsplus_iget(dir->i_sb, cnid);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (S_ISREG(inode->i_mode))
		HFSPLUS_I(inode)->linkid = linkid;
out:
	return d_splice_alias(inode, dentry);
fail:
	hfs_find_exit(&fd);
	return ERR_PTR(err);
}