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
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  struct erofs_dirent {int /*<<< orphan*/  nid; int /*<<< orphan*/  nameoff; int /*<<< orphan*/  file_type; } const erofs_dirent ;
struct dir_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int EFSCORRUPTED ; 
 TYPE_1__* EROFS_I (struct inode*) ; 
 unsigned int EROFS_NAME_LEN ; 
 int /*<<< orphan*/  debug_one_dentry (unsigned char,char const*,unsigned int) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char const*,unsigned int,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned char fs_ftype_to_dtype (int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int strnlen (char const*,unsigned int) ; 

__attribute__((used)) static int erofs_fill_dentries(struct inode *dir, struct dir_context *ctx,
			       void *dentry_blk, unsigned int *ofs,
			       unsigned int nameoff, unsigned int maxsize)
{
	struct erofs_dirent *de = dentry_blk + *ofs;
	const struct erofs_dirent *end = dentry_blk + nameoff;

	while (de < end) {
		const char *de_name;
		unsigned int de_namelen;
		unsigned char d_type;

		d_type = fs_ftype_to_dtype(de->file_type);

		nameoff = le16_to_cpu(de->nameoff);
		de_name = (char *)dentry_blk + nameoff;

		/* the last dirent in the block? */
		if (de + 1 >= end)
			de_namelen = strnlen(de_name, maxsize - nameoff);
		else
			de_namelen = le16_to_cpu(de[1].nameoff) - nameoff;

		/* a corrupted entry is found */
		if (nameoff + de_namelen > maxsize ||
		    de_namelen > EROFS_NAME_LEN) {
			erofs_err(dir->i_sb, "bogus dirent @ nid %llu",
				  EROFS_I(dir)->nid);
			DBG_BUGON(1);
			return -EFSCORRUPTED;
		}

		debug_one_dentry(d_type, de_name, de_namelen);
		if (!dir_emit(ctx, de_name, de_namelen,
			      le64_to_cpu(de->nid), d_type))
			/* stopped by some reason */
			return 1;
		++de;
		*ofs += sizeof(struct erofs_dirent);
	}
	*ofs = maxsize;
	return 0;
}