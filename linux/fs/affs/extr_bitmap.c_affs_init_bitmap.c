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
typedef  int u32 ;
struct super_block {int s_blocksize; int /*<<< orphan*/  s_id; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct affs_sb_info {int s_bmap_bits; int s_bmap_count; int s_partition_size; int s_reserved; TYPE_2__* s_root_bh; struct affs_bm_info* s_bitmap; int /*<<< orphan*/ * s_bmap_bh; int /*<<< orphan*/  s_last_bmap; } ;
struct affs_bm_info {void* bm_key; void* bm_free; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {scalar_t__ b_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  bm_flag; } ;

/* Variables and functions */
 TYPE_1__* AFFS_ROOT_TAIL (struct super_block*,TYPE_2__*) ; 
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SB_RDONLY ; 
 struct buffer_head* affs_bread (struct super_block*,void*) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int affs_checksum_block (struct super_block*,struct buffer_head*) ; 
 void* be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 struct affs_bm_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 void* memweight (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,void*,int /*<<< orphan*/ ) ; 

int affs_init_bitmap(struct super_block *sb, int *flags)
{
	struct affs_bm_info *bm;
	struct buffer_head *bmap_bh = NULL, *bh = NULL;
	__be32 *bmap_blk;
	u32 size, blk, end, offset, mask;
	int i, res = 0;
	struct affs_sb_info *sbi = AFFS_SB(sb);

	if (*flags & SB_RDONLY)
		return 0;

	if (!AFFS_ROOT_TAIL(sb, sbi->s_root_bh)->bm_flag) {
		pr_notice("Bitmap invalid - mounting %s read only\n", sb->s_id);
		*flags |= SB_RDONLY;
		return 0;
	}

	sbi->s_last_bmap = ~0;
	sbi->s_bmap_bh = NULL;
	sbi->s_bmap_bits = sb->s_blocksize * 8 - 32;
	sbi->s_bmap_count = (sbi->s_partition_size - sbi->s_reserved +
				 sbi->s_bmap_bits - 1) / sbi->s_bmap_bits;
	size = sbi->s_bmap_count * sizeof(*bm);
	bm = sbi->s_bitmap = kzalloc(size, GFP_KERNEL);
	if (!sbi->s_bitmap) {
		pr_err("Bitmap allocation failed\n");
		return -ENOMEM;
	}

	bmap_blk = (__be32 *)sbi->s_root_bh->b_data;
	blk = sb->s_blocksize / 4 - 49;
	end = blk + 25;

	for (i = sbi->s_bmap_count; i > 0; bm++, i--) {
		affs_brelse(bh);

		bm->bm_key = be32_to_cpu(bmap_blk[blk]);
		bh = affs_bread(sb, bm->bm_key);
		if (!bh) {
			pr_err("Cannot read bitmap\n");
			res = -EIO;
			goto out;
		}
		if (affs_checksum_block(sb, bh)) {
			pr_warn("Bitmap %u invalid - mounting %s read only.\n",
				bm->bm_key, sb->s_id);
			*flags |= SB_RDONLY;
			goto out;
		}
		pr_debug("read bitmap block %d: %d\n", blk, bm->bm_key);
		bm->bm_free = memweight(bh->b_data + 4, sb->s_blocksize - 4);

		/* Don't try read the extension if this is the last block,
		 * but we also need the right bm pointer below
		 */
		if (++blk < end || i == 1)
			continue;
		if (bmap_bh)
			affs_brelse(bmap_bh);
		bmap_bh = affs_bread(sb, be32_to_cpu(bmap_blk[blk]));
		if (!bmap_bh) {
			pr_err("Cannot read bitmap extension\n");
			res = -EIO;
			goto out;
		}
		bmap_blk = (__be32 *)bmap_bh->b_data;
		blk = 0;
		end = sb->s_blocksize / 4 - 1;
	}

	offset = (sbi->s_partition_size - sbi->s_reserved) % sbi->s_bmap_bits;
	mask = ~(0xFFFFFFFFU << (offset & 31));
	pr_debug("last word: %d %d %d\n", offset, offset / 32 + 1, mask);
	offset = offset / 32 + 1;

	if (mask) {
		u32 old, new;

		/* Mark unused bits in the last word as allocated */
		old = be32_to_cpu(((__be32 *)bh->b_data)[offset]);
		new = old & mask;
		//if (old != new) {
			((__be32 *)bh->b_data)[offset] = cpu_to_be32(new);
			/* fix checksum */
			//new -= old;
			//old = be32_to_cpu(*(__be32 *)bh->b_data);
			//*(__be32 *)bh->b_data = cpu_to_be32(old - new);
			//mark_buffer_dirty(bh);
		//}
		/* correct offset for the bitmap count below */
		//offset++;
	}
	while (++offset < sb->s_blocksize / 4)
		((__be32 *)bh->b_data)[offset] = 0;
	((__be32 *)bh->b_data)[0] = 0;
	((__be32 *)bh->b_data)[0] = cpu_to_be32(-affs_checksum_block(sb, bh));
	mark_buffer_dirty(bh);

	/* recalculate bitmap count for last block */
	bm--;
	bm->bm_free = memweight(bh->b_data + 4, sb->s_blocksize - 4);

out:
	affs_brelse(bh);
	affs_brelse(bmap_bh);
	return res;
}