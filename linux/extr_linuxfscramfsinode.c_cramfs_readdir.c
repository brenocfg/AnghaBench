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
typedef  int umode_t ;
struct super_block {int dummy; } ;
struct inode {unsigned int i_size; struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct dir_context {unsigned int pos; } ;
struct cramfs_inode {int namelen; int mode; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 scalar_t__ CRAMFS_MAXPATHLEN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OFFSET (struct inode*) ; 
 struct cramfs_inode* cramfs_read (struct super_block*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cramino (struct cramfs_inode*,scalar_t__) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,char*,int,int /*<<< orphan*/ ,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mutex ; 

__attribute__((used)) static int cramfs_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *inode = file_inode(file);
	struct super_block *sb = inode->i_sb;
	char *buf;
	unsigned int offset;

	/* Offset within the thing. */
	if (ctx->pos >= inode->i_size)
		return 0;
	offset = ctx->pos;
	/* Directory entries are always 4-byte aligned */
	if (offset & 3)
		return -EINVAL;

	buf = kmalloc(CRAMFS_MAXPATHLEN, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	while (offset < inode->i_size) {
		struct cramfs_inode *de;
		unsigned long nextoffset;
		char *name;
		ino_t ino;
		umode_t mode;
		int namelen;

		mutex_lock(&read_mutex);
		de = cramfs_read(sb, OFFSET(inode) + offset, sizeof(*de)+CRAMFS_MAXPATHLEN);
		name = (char *)(de+1);

		/*
		 * Namelengths on disk are shifted by two
		 * and the name padded out to 4-byte boundaries
		 * with zeroes.
		 */
		namelen = de->namelen << 2;
		memcpy(buf, name, namelen);
		ino = cramino(de, OFFSET(inode) + offset);
		mode = de->mode;
		mutex_unlock(&read_mutex);
		nextoffset = offset + sizeof(*de) + namelen;
		for (;;) {
			if (!namelen) {
				kfree(buf);
				return -EIO;
			}
			if (buf[namelen-1])
				break;
			namelen--;
		}
		if (!dir_emit(ctx, buf, namelen, ino, mode >> 12))
			break;

		ctx->pos = offset = nextoffset;
	}
	kfree(buf);
	return 0;
}