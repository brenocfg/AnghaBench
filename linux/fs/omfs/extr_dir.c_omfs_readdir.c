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
struct inode {int i_size; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct dir_context {int pos; } ;
struct buffer_head {int b_data; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int OMFS_DIR_START ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dir_emit_dots (struct file*,struct dir_context*) ; 
 struct inode* file_inode (struct file*) ; 
 struct buffer_head* omfs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omfs_fill_chain (struct inode*,struct dir_context*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int omfs_readdir(struct file *file, struct dir_context *ctx)
{
	struct inode *dir = file_inode(file);
	struct buffer_head *bh;
	__be64 *p;
	unsigned int hchain, hindex;
	int nbuckets;

	if (ctx->pos >> 32)
		return -EINVAL;

	if (ctx->pos < 1 << 20) {
		if (!dir_emit_dots(file, ctx))
			return 0;
		ctx->pos = 1 << 20;
	}

	nbuckets = (dir->i_size - OMFS_DIR_START) / 8;

	/* high 12 bits store bucket + 1 and low 20 bits store hash index */
	hchain = (ctx->pos >> 20) - 1;
	hindex = ctx->pos & 0xfffff;

	bh = omfs_bread(dir->i_sb, dir->i_ino);
	if (!bh)
		return -EINVAL;

	p = (__be64 *)(bh->b_data + OMFS_DIR_START) + hchain;

	for (; hchain < nbuckets; hchain++) {
		__u64 fsblock = be64_to_cpu(*p++);
		if (!omfs_fill_chain(dir, ctx, fsblock, hindex))
			break;
		hindex = 0;
		ctx->pos = (hchain+2) << 20;
	}
	brelse(bh);
	return 0;
}