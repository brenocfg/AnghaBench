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
typedef  int /*<<< orphan*/  wchar_t ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int isvfat; int /*<<< orphan*/  dotsOK; } ;
struct msdos_sb_info {int /*<<< orphan*/  s_lock; TYPE_1__ options; } ;
struct msdos_dir_entry {scalar_t__* name; int attr; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct fat_ioctl_filldir_callback {char const* longname; int long_len; unsigned char* shortname; int short_len; } ;
struct dir_context {int pos; } ;
struct buffer_head {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int ATTR_DIR ; 
 int ATTR_EXT ; 
 int ATTR_VOLUME ; 
 scalar_t__ DELETED_FLAG ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int ENOENT ; 
 int FAT_MAX_SHORT_SIZE ; 
 int FAT_MAX_UNI_CHARS ; 
 int FAT_MAX_UNI_SIZE ; 
 scalar_t__ IS_FREE (scalar_t__*) ; 
 int /*<<< orphan*/  MSDOS_DOT ; 
 int /*<<< orphan*/  MSDOS_DOTDOT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 scalar_t__ MSDOS_ROOT_INO ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int PARSE_EOF ; 
 int PARSE_INVALID ; 
 int PARSE_NOT_LONGNAME ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  __putname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char const*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_emit_dot (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  dir_emit_dotdot (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 int fat_get_entry (struct inode*,int*,struct buffer_head**,struct msdos_dir_entry**) ; 
 struct inode* fat_iget (struct super_block*,int) ; 
 int fat_make_i_pos (struct super_block*,struct buffer_head*,struct msdos_dir_entry*) ; 
 int fat_parse_long (struct inode*,int*,struct buffer_head**,struct msdos_dir_entry**,int /*<<< orphan*/ **,unsigned char*) ; 
 int fat_parse_short (struct super_block*,struct msdos_dir_entry*,unsigned char*,int /*<<< orphan*/ ) ; 
 int fat_uni_to_x8 (struct super_block*,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 unsigned long iunique (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  memcmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __fat_readdir(struct inode *inode, struct file *file,
			 struct dir_context *ctx, int short_only,
			 struct fat_ioctl_filldir_callback *both)
{
	struct super_block *sb = inode->i_sb;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);
	struct buffer_head *bh;
	struct msdos_dir_entry *de;
	unsigned char nr_slots;
	wchar_t *unicode = NULL;
	unsigned char bufname[FAT_MAX_SHORT_SIZE];
	int isvfat = sbi->options.isvfat;
	const char *fill_name = NULL;
	int fake_offset = 0;
	loff_t cpos;
	int short_len = 0, fill_len = 0;
	int ret = 0;

	mutex_lock(&sbi->s_lock);

	cpos = ctx->pos;
	/* Fake . and .. for the root directory. */
	if (inode->i_ino == MSDOS_ROOT_INO) {
		if (!dir_emit_dots(file, ctx))
			goto out;
		if (ctx->pos == 2) {
			fake_offset = 1;
			cpos = 0;
		}
	}
	if (cpos & (sizeof(struct msdos_dir_entry) - 1)) {
		ret = -ENOENT;
		goto out;
	}

	bh = NULL;
get_new:
	if (fat_get_entry(inode, &cpos, &bh, &de) == -1)
		goto end_of_dir;
parse_record:
	nr_slots = 0;
	/*
	 * Check for long filename entry, but if short_only, we don't
	 * need to parse long filename.
	 */
	if (isvfat && !short_only) {
		if (de->name[0] == DELETED_FLAG)
			goto record_end;
		if (de->attr != ATTR_EXT && (de->attr & ATTR_VOLUME))
			goto record_end;
		if (de->attr != ATTR_EXT && IS_FREE(de->name))
			goto record_end;
	} else {
		if ((de->attr & ATTR_VOLUME) || IS_FREE(de->name))
			goto record_end;
	}

	if (isvfat && de->attr == ATTR_EXT) {
		int status = fat_parse_long(inode, &cpos, &bh, &de,
					    &unicode, &nr_slots);
		if (status < 0) {
			bh = NULL;
			ret = status;
			goto end_of_dir;
		} else if (status == PARSE_INVALID)
			goto record_end;
		else if (status == PARSE_NOT_LONGNAME)
			goto parse_record;
		else if (status == PARSE_EOF)
			goto end_of_dir;

		if (nr_slots) {
			void *longname = unicode + FAT_MAX_UNI_CHARS;
			int size = PATH_MAX - FAT_MAX_UNI_SIZE;
			int len = fat_uni_to_x8(sb, unicode, longname, size);

			fill_name = longname;
			fill_len = len;
			/* !both && !short_only, so we don't need shortname. */
			if (!both)
				goto start_filldir;

			short_len = fat_parse_short(sb, de, bufname,
						    sbi->options.dotsOK);
			if (short_len == 0)
				goto record_end;
			/* hack for fat_ioctl_filldir() */
			both->longname = fill_name;
			both->long_len = fill_len;
			both->shortname = bufname;
			both->short_len = short_len;
			fill_name = NULL;
			fill_len = 0;
			goto start_filldir;
		}
	}

	short_len = fat_parse_short(sb, de, bufname, sbi->options.dotsOK);
	if (short_len == 0)
		goto record_end;

	fill_name = bufname;
	fill_len = short_len;

start_filldir:
	ctx->pos = cpos - (nr_slots + 1) * sizeof(struct msdos_dir_entry);
	if (fake_offset && ctx->pos < 2)
		ctx->pos = 2;

	if (!memcmp(de->name, MSDOS_DOT, MSDOS_NAME)) {
		if (!dir_emit_dot(file, ctx))
			goto fill_failed;
	} else if (!memcmp(de->name, MSDOS_DOTDOT, MSDOS_NAME)) {
		if (!dir_emit_dotdot(file, ctx))
			goto fill_failed;
	} else {
		unsigned long inum;
		loff_t i_pos = fat_make_i_pos(sb, bh, de);
		struct inode *tmp = fat_iget(sb, i_pos);
		if (tmp) {
			inum = tmp->i_ino;
			iput(tmp);
		} else
			inum = iunique(sb, MSDOS_ROOT_INO);
		if (!dir_emit(ctx, fill_name, fill_len, inum,
			    (de->attr & ATTR_DIR) ? DT_DIR : DT_REG))
			goto fill_failed;
	}

record_end:
	fake_offset = 0;
	ctx->pos = cpos;
	goto get_new;

end_of_dir:
	if (fake_offset && cpos < 2)
		ctx->pos = 2;
	else
		ctx->pos = cpos;
fill_failed:
	brelse(bh);
	if (unicode)
		__putname(unicode);
out:
	mutex_unlock(&sbi->s_lock);

	return ret;
}