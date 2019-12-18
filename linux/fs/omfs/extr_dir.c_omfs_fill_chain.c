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
typedef  int /*<<< orphan*/  u64 ;
struct omfs_inode {scalar_t__ i_type; int /*<<< orphan*/  i_name; int /*<<< orphan*/  i_sibling; int /*<<< orphan*/  i_head; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 unsigned char DT_DIR ; 
 unsigned char DT_REG ; 
 scalar_t__ OMFS_DIR ; 
 int /*<<< orphan*/  OMFS_NAMELEN ; 
 int /*<<< orphan*/  OMFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 struct buffer_head* omfs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omfs_is_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool omfs_fill_chain(struct inode *dir, struct dir_context *ctx,
		u64 fsblock, int hindex)
{
	/* follow chain in this bucket */
	while (fsblock != ~0) {
		struct buffer_head *bh = omfs_bread(dir->i_sb, fsblock);
		struct omfs_inode *oi;
		u64 self;
		unsigned char d_type;

		if (!bh)
			return true;

		oi = (struct omfs_inode *) bh->b_data;
		if (omfs_is_bad(OMFS_SB(dir->i_sb), &oi->i_head, fsblock)) {
			brelse(bh);
			return true;
		}

		self = fsblock;
		fsblock = be64_to_cpu(oi->i_sibling);

		/* skip visited nodes */
		if (hindex) {
			hindex--;
			brelse(bh);
			continue;
		}

		d_type = (oi->i_type == OMFS_DIR) ? DT_DIR : DT_REG;

		if (!dir_emit(ctx, oi->i_name,
			      strnlen(oi->i_name, OMFS_NAMELEN),
			      self, d_type)) {
			brelse(bh);
			return false;
		}
		brelse(bh);
		ctx->pos++;
	}
	return true;
}