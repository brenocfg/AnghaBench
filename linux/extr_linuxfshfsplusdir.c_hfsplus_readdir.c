#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_size; scalar_t__ i_ino; struct super_block* i_sb; } ;
struct hfsplus_readdir_data {int /*<<< orphan*/  key; int /*<<< orphan*/  list; struct file* file; } ;
struct hfsplus_cat_key {int dummy; } ;
struct hfsplus_cat_folder {int dummy; } ;
struct hfsplus_cat_file {int dummy; } ;
struct hfs_find_data {int entrylength; TYPE_8__* key; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; int /*<<< orphan*/  search_key; } ;
struct file {scalar_t__ f_pos; struct hfsplus_readdir_data* private_data; } ;
struct dir_context {scalar_t__ pos; } ;
struct TYPE_18__ {int /*<<< orphan*/  mode; } ;
struct TYPE_19__ {int /*<<< orphan*/  id; TYPE_5__ permissions; } ;
struct TYPE_17__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {int /*<<< orphan*/  parentID; } ;
struct TYPE_20__ {TYPE_6__ file; TYPE_4__ folder; int /*<<< orphan*/  type; TYPE_1__ thread; } ;
typedef  TYPE_7__ hfsplus_cat_entry ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  parent; } ;
struct TYPE_21__ {TYPE_2__ cat; } ;
struct TYPE_16__ {scalar_t__ i_ino; } ;
struct TYPE_13__ {int /*<<< orphan*/  open_dir_lock; int /*<<< orphan*/  open_dir_list; } ;
struct TYPE_12__ {TYPE_3__* hidden_dir; int /*<<< orphan*/  cat_tree; } ;

/* Variables and functions */
 unsigned int DT_BLK ; 
 unsigned int DT_CHR ; 
 unsigned int DT_DIR ; 
 unsigned int DT_FIFO ; 
 unsigned int DT_LNK ; 
 unsigned int DT_REG ; 
 unsigned int DT_SOCK ; 
 unsigned int DT_UNKNOWN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HFSPLUS_FILE ; 
 scalar_t__ HFSPLUS_FOLDER ; 
 scalar_t__ HFSPLUS_FOLDER_THREAD ; 
 TYPE_11__* HFSPLUS_I (struct inode*) ; 
 int HFSPLUS_MAX_STRLEN ; 
 int HFSPLUS_MIN_THREAD_SZ ; 
 TYPE_10__* HFSPLUS_SB (struct super_block*) ; 
 int NLS_MAX_CHARSET_SIZE ; 
 scalar_t__ S_ISBLK (scalar_t__) ; 
 scalar_t__ S_ISCHR (scalar_t__) ; 
 scalar_t__ S_ISFIFO (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 scalar_t__ S_ISREG (scalar_t__) ; 
 scalar_t__ S_ISSOCK (scalar_t__) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dir_emit_dot (struct file*,struct dir_context*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*,int /*<<< orphan*/ ) ; 
 int hfs_brec_goto (struct hfs_find_data*,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_rec_by_key ; 
 int /*<<< orphan*/  hfsplus_cat_build_key_with_cnid (struct super_block*,int /*<<< orphan*/ ,scalar_t__) ; 
 int hfsplus_uni2asc (struct super_block*,int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_8__*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfsplus_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct super_block *sb = inode->i_sb;
	int len, err;
	char *strbuf;
	hfsplus_cat_entry entry;
	struct hfs_find_data fd;
	struct hfsplus_readdir_data *rd;
	u16 type;

	if (file->f_pos >= inode->i_size)
		return 0;

	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &fd);
	if (err)
		return err;
	strbuf = kmalloc(NLS_MAX_CHARSET_SIZE * HFSPLUS_MAX_STRLEN + 1, GFP_KERNEL);
	if (!strbuf) {
		err = -ENOMEM;
		goto out;
	}
	hfsplus_cat_build_key_with_cnid(sb, fd.search_key, inode->i_ino);
	err = hfs_brec_find(&fd, hfs_find_rec_by_key);
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

		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset,
			fd.entrylength);
		if (be16_to_cpu(entry.type) != HFSPLUS_FOLDER_THREAD) {
			pr_err("bad catalog folder thread\n");
			err = -EIO;
			goto out;
		}
		if (fd.entrylength < HFSPLUS_MIN_THREAD_SZ) {
			pr_err("truncated catalog thread\n");
			err = -EIO;
			goto out;
		}
		if (!dir_emit(ctx, "..", 2,
			    be32_to_cpu(entry.thread.parentID), DT_DIR))
			goto out;
		ctx->pos = 2;
	}
	if (ctx->pos >= inode->i_size)
		goto out;
	err = hfs_brec_goto(&fd, ctx->pos - 1);
	if (err)
		goto out;
	for (;;) {
		if (be32_to_cpu(fd.key->cat.parent) != inode->i_ino) {
			pr_err("walked past end of dir\n");
			err = -EIO;
			goto out;
		}

		if (fd.entrylength > sizeof(entry) || fd.entrylength < 0) {
			err = -EIO;
			goto out;
		}

		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset,
			fd.entrylength);
		type = be16_to_cpu(entry.type);
		len = NLS_MAX_CHARSET_SIZE * HFSPLUS_MAX_STRLEN;
		err = hfsplus_uni2asc(sb, &fd.key->cat.name, strbuf, &len);
		if (err)
			goto out;
		if (type == HFSPLUS_FOLDER) {
			if (fd.entrylength <
					sizeof(struct hfsplus_cat_folder)) {
				pr_err("small dir entry\n");
				err = -EIO;
				goto out;
			}
			if (HFSPLUS_SB(sb)->hidden_dir &&
			    HFSPLUS_SB(sb)->hidden_dir->i_ino ==
					be32_to_cpu(entry.folder.id))
				goto next;
			if (!dir_emit(ctx, strbuf, len,
				    be32_to_cpu(entry.folder.id), DT_DIR))
				break;
		} else if (type == HFSPLUS_FILE) {
			u16 mode;
			unsigned type = DT_UNKNOWN;

			if (fd.entrylength < sizeof(struct hfsplus_cat_file)) {
				pr_err("small file entry\n");
				err = -EIO;
				goto out;
			}

			mode = be16_to_cpu(entry.file.permissions.mode);
			if (S_ISREG(mode))
				type = DT_REG;
			else if (S_ISLNK(mode))
				type = DT_LNK;
			else if (S_ISFIFO(mode))
				type = DT_FIFO;
			else if (S_ISCHR(mode))
				type = DT_CHR;
			else if (S_ISBLK(mode))
				type = DT_BLK;
			else if (S_ISSOCK(mode))
				type = DT_SOCK;

			if (!dir_emit(ctx, strbuf, len,
				      be32_to_cpu(entry.file.id), type))
				break;
		} else {
			pr_err("bad catalog entry type\n");
			err = -EIO;
			goto out;
		}
next:
		ctx->pos++;
		if (ctx->pos >= inode->i_size)
			goto out;
		err = hfs_brec_goto(&fd, 1);
		if (err)
			goto out;
	}
	rd = file->private_data;
	if (!rd) {
		rd = kmalloc(sizeof(struct hfsplus_readdir_data), GFP_KERNEL);
		if (!rd) {
			err = -ENOMEM;
			goto out;
		}
		file->private_data = rd;
		rd->file = file;
		spin_lock(&HFSPLUS_I(inode)->open_dir_lock);
		list_add(&rd->list, &HFSPLUS_I(inode)->open_dir_list);
		spin_unlock(&HFSPLUS_I(inode)->open_dir_lock);
	}
	/*
	 * Can be done after the list insertion; exclusion with
	 * hfsplus_delete_cat() is provided by directory lock.
	 */
	memcpy(&rd->key, fd.key, sizeof(struct hfsplus_cat_key));
out:
	kfree(strbuf);
	hfs_find_exit(&fd);
	return err;
}