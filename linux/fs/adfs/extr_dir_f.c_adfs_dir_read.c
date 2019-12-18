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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {unsigned int s_blocksize_bits; } ;
struct TYPE_3__ {scalar_t__ endmasseq; char endname; scalar_t__ dircheckbyte; } ;
struct TYPE_4__ {scalar_t__ startmasseq; TYPE_1__ new; int /*<<< orphan*/  startname; } ;
struct adfs_dir {int nr_buffers; struct super_block* sb; int /*<<< orphan*/ * bh; TYPE_2__ dirtail; TYPE_2__ dirhead; } ;

/* Variables and functions */
 int EIO ; 
 int __adfs_block_map (struct super_block*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ adfs_dir_checkbyte (struct adfs_dir*) ; 
 int /*<<< orphan*/  adfs_error (struct super_block*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufoff (int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sb_bread (struct super_block*,int) ; 

__attribute__((used)) static int adfs_dir_read(struct super_block *sb, u32 indaddr,
			 unsigned int size, struct adfs_dir *dir)
{
	const unsigned int blocksize_bits = sb->s_blocksize_bits;
	int blk = 0;

	/*
	 * Directories which are not a multiple of 2048 bytes
	 * are considered bad v2 [3.6]
	 */
	if (size & 2047)
		goto bad_dir;

	size >>= blocksize_bits;

	dir->nr_buffers = 0;
	dir->sb = sb;

	for (blk = 0; blk < size; blk++) {
		int phys;

		phys = __adfs_block_map(sb, indaddr, blk);
		if (!phys) {
			adfs_error(sb, "dir %06x has a hole at offset %d",
				   indaddr, blk);
			goto release_buffers;
		}

		dir->bh[blk] = sb_bread(sb, phys);
		if (!dir->bh[blk])
			goto release_buffers;
	}

	memcpy(&dir->dirhead, bufoff(dir->bh, 0), sizeof(dir->dirhead));
	memcpy(&dir->dirtail, bufoff(dir->bh, 2007), sizeof(dir->dirtail));

	if (dir->dirhead.startmasseq != dir->dirtail.new.endmasseq ||
	    memcmp(&dir->dirhead.startname, &dir->dirtail.new.endname, 4))
		goto bad_dir;

	if (memcmp(&dir->dirhead.startname, "Nick", 4) &&
	    memcmp(&dir->dirhead.startname, "Hugo", 4))
		goto bad_dir;

	if (adfs_dir_checkbyte(dir) != dir->dirtail.new.dircheckbyte)
		goto bad_dir;

	dir->nr_buffers = blk;

	return 0;

bad_dir:
	adfs_error(sb, "dir %06x is corrupted", indaddr);
release_buffers:
	for (blk -= 1; blk >= 0; blk -= 1)
		brelse(dir->bh[blk]);

	dir->sb = NULL;

	return -EIO;
}