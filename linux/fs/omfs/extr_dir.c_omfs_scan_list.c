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
struct omfs_inode {int /*<<< orphan*/  i_sibling; int /*<<< orphan*/  i_name; int /*<<< orphan*/  i_head; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 struct buffer_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  OMFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* omfs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omfs_is_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct buffer_head *omfs_scan_list(struct inode *dir, u64 block,
				const char *name, int namelen,
				u64 *prev_block)
{
	struct buffer_head *bh;
	struct omfs_inode *oi;
	int err = -ENOENT;
	*prev_block = ~0;

	while (block != ~0) {
		bh = omfs_bread(dir->i_sb, block);
		if (!bh) {
			err = -EIO;
			goto err;
		}

		oi = (struct omfs_inode *) bh->b_data;
		if (omfs_is_bad(OMFS_SB(dir->i_sb), &oi->i_head, block)) {
			brelse(bh);
			goto err;
		}

		if (strncmp(oi->i_name, name, namelen) == 0)
			return bh;

		*prev_block = block;
		block = be64_to_cpu(oi->i_sibling);
		brelse(bh);
	}
err:
	return ERR_PTR(err);
}