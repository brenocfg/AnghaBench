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
struct inode {int i_size; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int /*<<< orphan*/ * b_data; } ;

/* Variables and functions */
 size_t OMFS_DIR_START ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* omfs_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omfs_dir_is_empty(struct inode *inode)
{
	int nbuckets = (inode->i_size - OMFS_DIR_START) / 8;
	struct buffer_head *bh;
	u64 *ptr;
	int i;

	bh = omfs_bread(inode->i_sb, inode->i_ino);

	if (!bh)
		return 0;

	ptr = (u64 *) &bh->b_data[OMFS_DIR_START];

	for (i = 0; i < nbuckets; i++, ptr++)
		if (*ptr != ~0)
			break;

	brelse(bh);
	return *ptr != ~0;
}