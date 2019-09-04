#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  FlNum; } ;
struct TYPE_9__ {int /*<<< orphan*/  DirID; } ;
struct TYPE_8__ {int /*<<< orphan*/  ParID; } ;
union hfs_cat_rec {scalar_t__ type; TYPE_3__ file; TYPE_2__ dir; TYPE_1__ thread; } ;
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_size; scalar_t__ i_ino; struct super_block* i_sb; } ;
struct hfs_readdir_data {int /*<<< orphan*/  key; int /*<<< orphan*/  list; struct file* file; } ;
struct hfs_find_data {int entrylength; TYPE_4__* key; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; int /*<<< orphan*/  search_key; } ;
struct hfs_cat_key {int dummy; } ;
struct hfs_cat_file {int dummy; } ;
struct hfs_cat_dir {int dummy; } ;
struct file {struct hfs_readdir_data* private_data; } ;
struct dir_context {scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_14__ {int /*<<< orphan*/  open_dir_lock; int /*<<< orphan*/  open_dir_list; } ;
struct TYPE_13__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_12__ {int /*<<< orphan*/  CName; int /*<<< orphan*/  ParID; } ;
struct TYPE_11__ {TYPE_5__ cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HFS_CDR_DIR ; 
 scalar_t__ HFS_CDR_FIL ; 
 scalar_t__ HFS_CDR_THD ; 
 TYPE_7__* HFS_I (struct inode*) ; 
 int HFS_MAX_NAMELEN ; 
 TYPE_6__* HFS_SB (struct super_block*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit_dot (struct file*,struct dir_context*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,union hfs_cat_rec*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 
 int hfs_brec_goto (struct hfs_find_data*,int) ; 
 int /*<<< orphan*/  hfs_cat_build_key (struct super_block*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfs_mac2asc (struct super_block*,char*,int /*<<< orphan*/ *) ; 
 struct hfs_readdir_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfs_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct super_block *sb = inode->i_sb;
	int len, err;
	char strbuf[HFS_MAX_NAMELEN];
	union hfs_cat_rec entry;
	struct hfs_find_data fd;
	struct hfs_readdir_data *rd;
	u16 type;

	if (ctx->pos >= inode->i_size)
		return 0;

	err = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	if (err)
		return err;
	hfs_cat_build_key(sb, fd.search_key, inode->i_ino, NULL);
	err = hfs_brec_find(&fd);
	if (err)
		goto out;

	if (ctx->pos == 0) {
		/* This is completely artificial... */
		if (!dir_emit_dot(file, ctx))
			goto out;
		ctx->pos = 1;
	}
	if (ctx->pos == 1) {
		if (fd.entrylength > sizeof(entry) || fd.entrylength < 0) {
			err = -EIO;
			goto out;
		}

		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset, fd.entrylength);
		if (entry.type != HFS_CDR_THD) {
			pr_err("bad catalog folder thread\n");
			err = -EIO;
			goto out;
		}
		//if (fd.entrylength < HFS_MIN_THREAD_SZ) {
		//	pr_err("truncated catalog thread\n");
		//	err = -EIO;
		//	goto out;
		//}
		if (!dir_emit(ctx, "..", 2,
			    be32_to_cpu(entry.thread.ParID), DT_DIR))
			goto out;
		ctx->pos = 2;
	}
	if (ctx->pos >= inode->i_size)
		goto out;
	err = hfs_brec_goto(&fd, ctx->pos - 1);
	if (err)
		goto out;

	for (;;) {
		if (be32_to_cpu(fd.key->cat.ParID) != inode->i_ino) {
			pr_err("walked past end of dir\n");
			err = -EIO;
			goto out;
		}

		if (fd.entrylength > sizeof(entry) || fd.entrylength < 0) {
			err = -EIO;
			goto out;
		}

		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset, fd.entrylength);
		type = entry.type;
		len = hfs_mac2asc(sb, strbuf, &fd.key->cat.CName);
		if (type == HFS_CDR_DIR) {
			if (fd.entrylength < sizeof(struct hfs_cat_dir)) {
				pr_err("small dir entry\n");
				err = -EIO;
				goto out;
			}
			if (!dir_emit(ctx, strbuf, len,
				    be32_to_cpu(entry.dir.DirID), DT_DIR))
				break;
		} else if (type == HFS_CDR_FIL) {
			if (fd.entrylength < sizeof(struct hfs_cat_file)) {
				pr_err("small file entry\n");
				err = -EIO;
				goto out;
			}
			if (!dir_emit(ctx, strbuf, len,
				    be32_to_cpu(entry.file.FlNum), DT_REG))
				break;
		} else {
			pr_err("bad catalog entry type %d\n", type);
			err = -EIO;
			goto out;
		}
		ctx->pos++;
		if (ctx->pos >= inode->i_size)
			goto out;
		err = hfs_brec_goto(&fd, 1);
		if (err)
			goto out;
	}
	rd = file->private_data;
	if (!rd) {
		rd = kmalloc(sizeof(struct hfs_readdir_data), GFP_KERNEL);
		if (!rd) {
			err = -ENOMEM;
			goto out;
		}
		file->private_data = rd;
		rd->file = file;
		spin_lock(&HFS_I(inode)->open_dir_lock);
		list_add(&rd->list, &HFS_I(inode)->open_dir_list);
		spin_unlock(&HFS_I(inode)->open_dir_lock);
	}
	/*
	 * Can be done after the list insertion; exclusion with
	 * hfs_delete_cat() is provided by directory lock.
	 */
	memcpy(&rd->key, &fd.key->cat, sizeof(struct hfs_cat_key));
out:
	hfs_find_exit(&fd);
	return err;
}