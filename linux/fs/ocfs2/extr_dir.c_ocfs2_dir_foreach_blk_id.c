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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_inline_data {scalar_t__ id_data; } ;
struct ocfs2_dir_entry {int /*<<< orphan*/  rec_len; int /*<<< orphan*/  file_type; int /*<<< orphan*/  inode; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct ocfs2_inline_data i_data; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int dummy; } ;
struct dir_context {unsigned long pos; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ OCFS2_DIR_REC_LEN (int) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_ftype_to_dtype (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_eq_iversion (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_check_dir_entry (struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,unsigned long) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_dir_foreach_blk_id(struct inode *inode,
				    u64 *f_version,
				    struct dir_context *ctx)
{
	int ret, i;
	unsigned long offset = ctx->pos;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	struct ocfs2_inline_data *data;
	struct ocfs2_dir_entry *de;

	ret = ocfs2_read_inode_block(inode, &di_bh);
	if (ret) {
		mlog(ML_ERROR, "Unable to read inode block for dir %llu\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		goto out;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	while (ctx->pos < i_size_read(inode)) {
		/* If the dir block has changed since the last call to
		 * readdir(2), then we might be pointing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		if (!inode_eq_iversion(inode, *f_version)) {
			for (i = 0; i < i_size_read(inode) && i < offset; ) {
				de = (struct ocfs2_dir_entry *)
					(data->id_data + i);
				/* It's too expensive to do a full
				 * dirent test each time round this
				 * loop, but we do have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				if (le16_to_cpu(de->rec_len) <
				    OCFS2_DIR_REC_LEN(1))
					break;
				i += le16_to_cpu(de->rec_len);
			}
			ctx->pos = offset = i;
			*f_version = inode_query_iversion(inode);
		}

		de = (struct ocfs2_dir_entry *) (data->id_data + ctx->pos);
		if (!ocfs2_check_dir_entry(inode, de, di_bh, ctx->pos)) {
			/* On error, skip the f_pos to the end. */
			ctx->pos = i_size_read(inode);
			break;
		}
		offset += le16_to_cpu(de->rec_len);
		if (le64_to_cpu(de->inode)) {
			if (!dir_emit(ctx, de->name, de->name_len,
				      le64_to_cpu(de->inode),
				      fs_ftype_to_dtype(de->file_type)))
				goto out;
		}
		ctx->pos += le16_to_cpu(de->rec_len);
	}
out:
	brelse(di_bh);
	return 0;
}