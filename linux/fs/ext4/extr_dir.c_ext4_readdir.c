#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; TYPE_2__* s_bdev; } ;
struct inode {int i_size; int i_blkbits; int i_blocks; struct super_block* i_sb; } ;
struct fscrypt_str {int len; int /*<<< orphan*/ * name; } ;
struct TYPE_7__ {int prev_pos; } ;
struct file {int /*<<< orphan*/  f_version; TYPE_3__ f_ra; } ;
struct ext4_map_blocks {int m_lblk; int m_len; int m_pblk; } ;
struct ext4_dir_entry_2 {int name_len; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  file_type; int /*<<< orphan*/  inode; int /*<<< orphan*/ * name; } ;
struct dir_context {int pos; } ;
struct buffer_head {int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_6__ {TYPE_1__* bd_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOKEY ; 
 int ERESTARTSYS ; 
 int ERR_BAD_DX_DIR ; 
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 scalar_t__ EXT4_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXT4_ERROR_FILE (struct file*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  EXT4_INODE_INDEX ; 
 int /*<<< orphan*/  EXT4_NAME_LEN ; 
 struct fscrypt_str FSTR_INIT (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_verified (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_relax_shared (struct inode*) ; 
 struct buffer_head* ext4_bread (int /*<<< orphan*/ *,struct inode*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_check_dir_entry (struct inode*,struct file*,struct ext4_dir_entry_2*,struct buffer_head*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_dirblock_csum_verify (struct inode*,struct buffer_head*) ; 
 int ext4_dx_readdir (struct file*,struct dir_context*) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int ext4_map_blocks (int /*<<< orphan*/ *,struct inode*,struct ext4_map_blocks*,int /*<<< orphan*/ ) ; 
 int ext4_read_inline_dir (struct file*,struct dir_context*,int*) ; 
 scalar_t__ ext4_rec_len_from_disk (int /*<<< orphan*/ ,int) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int fscrypt_fname_alloc_buffer (struct inode*,int /*<<< orphan*/ ,struct fscrypt_str*) ; 
 int fscrypt_fname_disk_to_usr (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fscrypt_str*,struct fscrypt_str*) ; 
 int /*<<< orphan*/  fscrypt_fname_free_buffer (struct fscrypt_str*) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int /*<<< orphan*/  get_dtype (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_eq_iversion (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 scalar_t__ is_dx_dir (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_sync_readahead (int /*<<< orphan*/ ,TYPE_3__*,struct file*,int,int) ; 
 int /*<<< orphan*/  ra_has_index (TYPE_3__*,int) ; 
 int /*<<< orphan*/  set_buffer_verified (struct buffer_head*) ; 

__attribute__((used)) static int ext4_readdir(struct file *file, struct dir_context *ctx)
{
	unsigned int offset;
	int i;
	struct ext4_dir_entry_2 *de;
	int err;
	struct inode *inode = file_inode(file);
	struct super_block *sb = inode->i_sb;
	struct buffer_head *bh = NULL;
	struct fscrypt_str fstr = FSTR_INIT(NULL, 0);

	if (IS_ENCRYPTED(inode)) {
		err = fscrypt_get_encryption_info(inode);
		if (err && err != -ENOKEY)
			return err;
	}

	if (is_dx_dir(inode)) {
		err = ext4_dx_readdir(file, ctx);
		if (err != ERR_BAD_DX_DIR) {
			return err;
		}
		/*
		 * We don't set the inode dirty flag since it's not
		 * critical that it get flushed back to the disk.
		 */
		ext4_clear_inode_flag(file_inode(file),
				      EXT4_INODE_INDEX);
	}

	if (ext4_has_inline_data(inode)) {
		int has_inline_data = 1;
		err = ext4_read_inline_dir(file, ctx,
					   &has_inline_data);
		if (has_inline_data)
			return err;
	}

	if (IS_ENCRYPTED(inode)) {
		err = fscrypt_fname_alloc_buffer(inode, EXT4_NAME_LEN, &fstr);
		if (err < 0)
			return err;
	}

	while (ctx->pos < inode->i_size) {
		struct ext4_map_blocks map;

		if (fatal_signal_pending(current)) {
			err = -ERESTARTSYS;
			goto errout;
		}
		cond_resched();
		offset = ctx->pos & (sb->s_blocksize - 1);
		map.m_lblk = ctx->pos >> EXT4_BLOCK_SIZE_BITS(sb);
		map.m_len = 1;
		err = ext4_map_blocks(NULL, inode, &map, 0);
		if (err == 0) {
			/* m_len should never be zero but let's avoid
			 * an infinite loop if it somehow is */
			if (map.m_len == 0)
				map.m_len = 1;
			ctx->pos += map.m_len * sb->s_blocksize;
			continue;
		}
		if (err > 0) {
			pgoff_t index = map.m_pblk >>
					(PAGE_SHIFT - inode->i_blkbits);
			if (!ra_has_index(&file->f_ra, index))
				page_cache_sync_readahead(
					sb->s_bdev->bd_inode->i_mapping,
					&file->f_ra, file,
					index, 1);
			file->f_ra.prev_pos = (loff_t)index << PAGE_SHIFT;
			bh = ext4_bread(NULL, inode, map.m_lblk, 0);
			if (IS_ERR(bh)) {
				err = PTR_ERR(bh);
				bh = NULL;
				goto errout;
			}
		}

		if (!bh) {
			/* corrupt size?  Maybe no more blocks to read */
			if (ctx->pos > inode->i_blocks << 9)
				break;
			ctx->pos += sb->s_blocksize - offset;
			continue;
		}

		/* Check the checksum */
		if (!buffer_verified(bh) &&
		    !ext4_dirblock_csum_verify(inode, bh)) {
			EXT4_ERROR_FILE(file, 0, "directory fails checksum "
					"at offset %llu",
					(unsigned long long)ctx->pos);
			ctx->pos += sb->s_blocksize - offset;
			brelse(bh);
			bh = NULL;
			continue;
		}
		set_buffer_verified(bh);

		/* If the dir block has changed since the last call to
		 * readdir(2), then we might be pointing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		if (!inode_eq_iversion(inode, file->f_version)) {
			for (i = 0; i < sb->s_blocksize && i < offset; ) {
				de = (struct ext4_dir_entry_2 *)
					(bh->b_data + i);
				/* It's too expensive to do a full
				 * dirent test each time round this
				 * loop, but we do have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				if (ext4_rec_len_from_disk(de->rec_len,
					sb->s_blocksize) < EXT4_DIR_REC_LEN(1))
					break;
				i += ext4_rec_len_from_disk(de->rec_len,
							    sb->s_blocksize);
			}
			offset = i;
			ctx->pos = (ctx->pos & ~(sb->s_blocksize - 1))
				| offset;
			file->f_version = inode_query_iversion(inode);
		}

		while (ctx->pos < inode->i_size
		       && offset < sb->s_blocksize) {
			de = (struct ext4_dir_entry_2 *) (bh->b_data + offset);
			if (ext4_check_dir_entry(inode, file, de, bh,
						 bh->b_data, bh->b_size,
						 offset)) {
				/*
				 * On error, skip to the next block
				 */
				ctx->pos = (ctx->pos |
						(sb->s_blocksize - 1)) + 1;
				break;
			}
			offset += ext4_rec_len_from_disk(de->rec_len,
					sb->s_blocksize);
			if (le32_to_cpu(de->inode)) {
				if (!IS_ENCRYPTED(inode)) {
					if (!dir_emit(ctx, de->name,
					    de->name_len,
					    le32_to_cpu(de->inode),
					    get_dtype(sb, de->file_type)))
						goto done;
				} else {
					int save_len = fstr.len;
					struct fscrypt_str de_name =
							FSTR_INIT(de->name,
								de->name_len);

					/* Directory is encrypted */
					err = fscrypt_fname_disk_to_usr(inode,
						0, 0, &de_name, &fstr);
					de_name = fstr;
					fstr.len = save_len;
					if (err)
						goto errout;
					if (!dir_emit(ctx,
					    de_name.name, de_name.len,
					    le32_to_cpu(de->inode),
					    get_dtype(sb, de->file_type)))
						goto done;
				}
			}
			ctx->pos += ext4_rec_len_from_disk(de->rec_len,
						sb->s_blocksize);
		}
		if ((ctx->pos < inode->i_size) && !dir_relax_shared(inode))
			goto done;
		brelse(bh);
		bh = NULL;
		offset = 0;
	}
done:
	err = 0;
errout:
	fscrypt_fname_free_buffer(&fstr);
	brelse(bh);
	return err;
}