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
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct blk_plug {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_P_SB (struct page*) ; 
 int /*<<< orphan*/  NIDS_PER_BLOCK ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  f2fs_ra_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nid (struct page*,int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f2fs_ra_node_pages(struct page *parent, int start, int n)
{
	struct f2fs_sb_info *sbi = F2FS_P_SB(parent);
	struct blk_plug plug;
	int i, end;
	nid_t nid;

	blk_start_plug(&plug);

	/* Then, try readahead for siblings of the desired node */
	end = start + n;
	end = min(end, NIDS_PER_BLOCK);
	for (i = start; i < end; i++) {
		nid = get_nid(parent, i, false);
		f2fs_ra_node_page(sbi, nid);
	}

	blk_finish_plug(&plug);
}