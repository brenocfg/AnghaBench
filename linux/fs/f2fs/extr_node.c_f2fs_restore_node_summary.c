#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct f2fs_summary_block {struct f2fs_summary* entries; } ;
struct f2fs_summary {scalar_t__ ofs_in_node; scalar_t__ version; int /*<<< orphan*/  nid; } ;
struct f2fs_sb_info {int blocks_per_seg; } ;
struct TYPE_2__ {int /*<<< orphan*/  nid; } ;
struct f2fs_node {TYPE_1__ footer; } ;
typedef  int block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_MAX_PAGES ; 
 struct f2fs_node* F2FS_NODE (struct page*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  META_POR ; 
 int PTR_ERR (struct page*) ; 
 int START_BLOCK (struct f2fs_sb_info*,unsigned int) ; 
 struct page* f2fs_get_tmp_page (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages (struct f2fs_sb_info*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

int f2fs_restore_node_summary(struct f2fs_sb_info *sbi,
			unsigned int segno, struct f2fs_summary_block *sum)
{
	struct f2fs_node *rn;
	struct f2fs_summary *sum_entry;
	block_t addr;
	int i, idx, last_offset, nrpages;

	/* scan the node segment */
	last_offset = sbi->blocks_per_seg;
	addr = START_BLOCK(sbi, segno);
	sum_entry = &sum->entries[0];

	for (i = 0; i < last_offset; i += nrpages, addr += nrpages) {
		nrpages = min(last_offset - i, BIO_MAX_PAGES);

		/* readahead node pages */
		f2fs_ra_meta_pages(sbi, addr, nrpages, META_POR, true);

		for (idx = addr; idx < addr + nrpages; idx++) {
			struct page *page = f2fs_get_tmp_page(sbi, idx);

			if (IS_ERR(page))
				return PTR_ERR(page);

			rn = F2FS_NODE(page);
			sum_entry->nid = rn->footer.nid;
			sum_entry->version = 0;
			sum_entry->ofs_in_node = 0;
			sum_entry++;
			f2fs_put_page(page, 1);
		}

		invalidate_mapping_pages(META_MAPPING(sbi), addr,
							addr + nrpages);
	}
	return 0;
}