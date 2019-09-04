#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct fscrypt_str {int len; int /*<<< orphan*/  name; } ;
struct f2fs_sb_info {int readdir_ra; } ;
struct f2fs_dir_entry {scalar_t__ name_len; int /*<<< orphan*/  ino; scalar_t__ hash_code; } ;
struct f2fs_dentry_ptr {unsigned long max; int /*<<< orphan*/  inode; int /*<<< orphan*/ * filename; struct f2fs_dir_entry* dentry; int /*<<< orphan*/  bitmap; } ;
struct dir_context {unsigned int pos; } ;

/* Variables and functions */
 unsigned char DT_UNKNOWN ; 
 struct f2fs_sb_info* F2FS_I_SB (int /*<<< orphan*/ ) ; 
 struct fscrypt_str FSTR_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_DENTRY_SLOTS (int) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ f2fs_encrypted_inode (int /*<<< orphan*/ ) ; 
 unsigned char f2fs_get_de_type (struct f2fs_dir_entry*) ; 
 int /*<<< orphan*/  f2fs_ra_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 unsigned int find_next_bit_le (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int fscrypt_fname_disk_to_usr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fscrypt_str*,struct fscrypt_str*) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int f2fs_fill_dentries(struct dir_context *ctx, struct f2fs_dentry_ptr *d,
			unsigned int start_pos, struct fscrypt_str *fstr)
{
	unsigned char d_type = DT_UNKNOWN;
	unsigned int bit_pos;
	struct f2fs_dir_entry *de = NULL;
	struct fscrypt_str de_name = FSTR_INIT(NULL, 0);
	struct f2fs_sb_info *sbi = F2FS_I_SB(d->inode);

	bit_pos = ((unsigned long)ctx->pos % d->max);

	while (bit_pos < d->max) {
		bit_pos = find_next_bit_le(d->bitmap, d->max, bit_pos);
		if (bit_pos >= d->max)
			break;

		de = &d->dentry[bit_pos];
		if (de->name_len == 0) {
			bit_pos++;
			ctx->pos = start_pos + bit_pos;
			continue;
		}

		d_type = f2fs_get_de_type(de);

		de_name.name = d->filename[bit_pos];
		de_name.len = le16_to_cpu(de->name_len);

		if (f2fs_encrypted_inode(d->inode)) {
			int save_len = fstr->len;
			int err;

			err = fscrypt_fname_disk_to_usr(d->inode,
						(u32)de->hash_code, 0,
						&de_name, fstr);
			if (err)
				return err;

			de_name = *fstr;
			fstr->len = save_len;
		}

		if (!dir_emit(ctx, de_name.name, de_name.len,
					le32_to_cpu(de->ino), d_type))
			return 1;

		if (sbi->readdir_ra == 1)
			f2fs_ra_node_page(sbi, le32_to_cpu(de->ino));

		bit_pos += GET_DENTRY_SLOTS(le16_to_cpu(de->name_len));
		ctx->pos = start_pos + bit_pos;
	}
	return 0;
}