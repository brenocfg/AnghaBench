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
typedef  struct erofs_dirent {size_t file_type; int /*<<< orphan*/  nid; int /*<<< orphan*/  nameoff; } const erofs_dirent ;
struct dir_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 unsigned char DT_UNKNOWN ; 
 int EIO ; 
 size_t EROFS_FT_MAX ; 
 unsigned int EROFS_NAME_LEN ; 
 int /*<<< orphan*/  debug_one_dentry (unsigned char,char const*,unsigned int) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char const*,unsigned int,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char* erofs_filetype_table ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int strnlen (char const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int erofs_fill_dentries(struct dir_context *ctx,
	void *dentry_blk, unsigned *ofs,
	unsigned nameoff, unsigned maxsize)
{
	struct erofs_dirent *de = dentry_blk;
	const struct erofs_dirent *end = dentry_blk + nameoff;

	de = dentry_blk + *ofs;
	while (de < end) {
		const char *de_name;
		unsigned int de_namelen;
		unsigned char d_type;

		if (de->file_type < EROFS_FT_MAX)
			d_type = erofs_filetype_table[de->file_type];
		else
			d_type = DT_UNKNOWN;

		nameoff = le16_to_cpu(de->nameoff);
		de_name = (char *)dentry_blk + nameoff;

		/* the last dirent in the block? */
		if (de + 1 >= end)
			de_namelen = strnlen(de_name, maxsize - nameoff);
		else
			de_namelen = le16_to_cpu(de[1].nameoff) - nameoff;

		/* a corrupted entry is found */
		if (unlikely(nameoff + de_namelen > maxsize ||
			     de_namelen > EROFS_NAME_LEN)) {
			DBG_BUGON(1);
			return -EIO;
		}

		debug_one_dentry(d_type, de_name, de_namelen);
		if (!dir_emit(ctx, de_name, de_namelen,
					le64_to_cpu(de->nid), d_type))
			/* stoped by some reason */
			return 1;
		++de;
		*ofs += sizeof(struct erofs_dirent);
	}
	*ofs = maxsize;
	return 0;
}