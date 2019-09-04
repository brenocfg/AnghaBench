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
typedef  int secno ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_claim_alloc (struct super_block*,int) ; 
 int /*<<< orphan*/ * hpfs_map_bitmap (struct super_block*,int,struct quad_buffer_head*,char*) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

int hpfs_alloc_if_possible(struct super_block *s, secno sec)
{
	struct quad_buffer_head qbh;
	__le32 *bmp;
	if (!(bmp = hpfs_map_bitmap(s, sec >> 14, &qbh, "aip"))) goto end;
	if (le32_to_cpu(bmp[(sec & 0x3fff) >> 5]) & (1 << (sec & 0x1f))) {
		bmp[(sec & 0x3fff) >> 5] &= cpu_to_le32(~(1 << (sec & 0x1f)));
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brelse4(&qbh);
		hpfs_claim_alloc(s, sec);
		return 1;
	}
	hpfs_brelse4(&qbh);
	end:
	return 0;
}