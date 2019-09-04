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
struct inode {int i_size; TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct dir_context {int pos; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct bfs_dirent {scalar_t__ ino; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int i_sblock; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int BFS_BSIZE ; 
 int BFS_BSIZE_BITS ; 
 int BFS_DIRENT_SIZE ; 
 TYPE_2__* BFS_I (struct inode*) ; 
 int /*<<< orphan*/  BFS_NAMELEN ; 
 int /*<<< orphan*/  DT_UNKNOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (TYPE_1__*,int) ; 
 int strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfs_readdir(struct file *f, struct dir_context *ctx)
{
	struct inode *dir = file_inode(f);
	struct buffer_head *bh;
	struct bfs_dirent *de;
	unsigned int offset;
	int block;

	if (ctx->pos & (BFS_DIRENT_SIZE - 1)) {
		printf("Bad f_pos=%08lx for %s:%08lx\n",
					(unsigned long)ctx->pos,
					dir->i_sb->s_id, dir->i_ino);
		return -EINVAL;
	}

	while (ctx->pos < dir->i_size) {
		offset = ctx->pos & (BFS_BSIZE - 1);
		block = BFS_I(dir)->i_sblock + (ctx->pos >> BFS_BSIZE_BITS);
		bh = sb_bread(dir->i_sb, block);
		if (!bh) {
			ctx->pos += BFS_BSIZE - offset;
			continue;
		}
		do {
			de = (struct bfs_dirent *)(bh->b_data + offset);
			if (de->ino) {
				int size = strnlen(de->name, BFS_NAMELEN);
				if (!dir_emit(ctx, de->name, size,
						le16_to_cpu(de->ino),
						DT_UNKNOWN)) {
					brelse(bh);
					return 0;
				}
			}
			offset += BFS_DIRENT_SIZE;
			ctx->pos += BFS_DIRENT_SIZE;
		} while ((offset < BFS_BSIZE) && (ctx->pos < dir->i_size));
		brelse(bh);
	}
	return 0;
}