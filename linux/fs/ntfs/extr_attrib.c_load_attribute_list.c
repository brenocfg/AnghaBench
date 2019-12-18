#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct super_block {unsigned long s_blocksize; unsigned char s_blocksize_bits; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int s64 ;
struct TYPE_7__ {int length; scalar_t__ vcn; } ;
typedef  TYPE_1__ runlist_element ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_1__* rl; } ;
typedef  TYPE_2__ runlist ;
struct TYPE_9__ {unsigned char cluster_size_bits; struct super_block* sb; } ;
typedef  TYPE_3__ ntfs_volume ;
typedef  unsigned char LCN ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int /*<<< orphan*/  ntfs_error (struct super_block*,char*) ; 
 unsigned char ntfs_rl_vcn_to_lcn (TYPE_1__*,scalar_t__) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int load_attribute_list(ntfs_volume *vol, runlist *runlist, u8 *al_start,
		const s64 size, const s64 initialized_size)
{
	LCN lcn;
	u8 *al = al_start;
	u8 *al_end = al + initialized_size;
	runlist_element *rl;
	struct buffer_head *bh;
	struct super_block *sb;
	unsigned long block_size;
	unsigned long block, max_block;
	int err = 0;
	unsigned char block_size_bits;

	ntfs_debug("Entering.");
	if (!vol || !runlist || !al || size <= 0 || initialized_size < 0 ||
			initialized_size > size)
		return -EINVAL;
	if (!initialized_size) {
		memset(al, 0, size);
		return 0;
	}
	sb = vol->sb;
	block_size = sb->s_blocksize;
	block_size_bits = sb->s_blocksize_bits;
	down_read(&runlist->lock);
	rl = runlist->rl;
	if (!rl) {
		ntfs_error(sb, "Cannot read attribute list since runlist is "
				"missing.");
		goto err_out;	
	}
	/* Read all clusters specified by the runlist one run at a time. */
	while (rl->length) {
		lcn = ntfs_rl_vcn_to_lcn(rl, rl->vcn);
		ntfs_debug("Reading vcn = 0x%llx, lcn = 0x%llx.",
				(unsigned long long)rl->vcn,
				(unsigned long long)lcn);
		/* The attribute list cannot be sparse. */
		if (lcn < 0) {
			ntfs_error(sb, "ntfs_rl_vcn_to_lcn() failed.  Cannot "
					"read attribute list.");
			goto err_out;
		}
		block = lcn << vol->cluster_size_bits >> block_size_bits;
		/* Read the run from device in chunks of block_size bytes. */
		max_block = block + (rl->length << vol->cluster_size_bits >>
				block_size_bits);
		ntfs_debug("max_block = 0x%lx.", max_block);
		do {
			ntfs_debug("Reading block = 0x%lx.", block);
			bh = sb_bread(sb, block);
			if (!bh) {
				ntfs_error(sb, "sb_bread() failed. Cannot "
						"read attribute list.");
				goto err_out;
			}
			if (al + block_size >= al_end)
				goto do_final;
			memcpy(al, bh->b_data, block_size);
			brelse(bh);
			al += block_size;
		} while (++block < max_block);
		rl++;
	}
	if (initialized_size < size) {
initialize:
		memset(al_start + initialized_size, 0, size - initialized_size);
	}
done:
	up_read(&runlist->lock);
	return err;
do_final:
	if (al < al_end) {
		/*
		 * Partial block.
		 *
		 * Note: The attribute list can be smaller than its allocation
		 * by multiple clusters.  This has been encountered by at least
		 * two people running Windows XP, thus we cannot do any
		 * truncation sanity checking here. (AIA)
		 */
		memcpy(al, bh->b_data, al_end - al);
		brelse(bh);
		if (initialized_size < size)
			goto initialize;
		goto done;
	}
	brelse(bh);
	/* Real overflow! */
	ntfs_error(sb, "Attribute list buffer overflow. Read attribute list "
			"is truncated.");
err_out:
	err = -EIO;
	goto done;
}