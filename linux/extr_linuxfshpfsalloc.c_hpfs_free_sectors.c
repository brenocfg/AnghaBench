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
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
struct hpfs_sb_info {int sb_max_fwd_alloc; } ;
typedef  int secno ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_claim_free (struct super_block*,int) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,int) ; 
 int /*<<< orphan*/ * hpfs_map_bitmap (struct super_block*,int,struct quad_buffer_head*,char*) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

void hpfs_free_sectors(struct super_block *s, secno sec, unsigned n)
{
	struct quad_buffer_head qbh;
	__le32 *bmp;
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	/*pr_info("2 - ");*/
	if (!n) return;
	if (sec < 0x12) {
		hpfs_error(s, "Trying to free reserved sector %08x", sec);
		return;
	}
	sbi->sb_max_fwd_alloc += n > 0xffff ? 0xffff : n;
	if (sbi->sb_max_fwd_alloc > 0xffffff) sbi->sb_max_fwd_alloc = 0xffffff;
	new_map:
	if (!(bmp = hpfs_map_bitmap(s, sec >> 14, &qbh, "free"))) {
		return;
	}	
	new_tst:
	if ((le32_to_cpu(bmp[(sec & 0x3fff) >> 5]) >> (sec & 0x1f) & 1)) {
		hpfs_error(s, "sector %08x not allocated", sec);
		hpfs_brelse4(&qbh);
		return;
	}
	bmp[(sec & 0x3fff) >> 5] |= cpu_to_le32(1 << (sec & 0x1f));
	hpfs_claim_free(s, sec);
	if (!--n) {
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
		return;
	}	
	if (!(++sec & 0x3fff)) {
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
		goto new_map;
	}
	goto new_tst;
}