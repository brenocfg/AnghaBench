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
struct f2fs_nm_info {int next_scan_nid; int max_nid; int* nid_cnt; int ra_nid_pages; int /*<<< orphan*/  nat_tree_lock; int /*<<< orphan*/  nat_block_bitmap; } ;
typedef  int nid_t ;

/* Variables and functions */
 size_t FREE_NID ; 
 int /*<<< orphan*/  FREE_NIDS ; 
 int FREE_NID_PAGES ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  META_NAT ; 
 int /*<<< orphan*/  NAT_BLOCK_OFFSET (int) ; 
 int NAT_ENTRY_PER_BLOCK ; 
 struct f2fs_nm_info* NM_I (struct f2fs_sb_info*) ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_available_free_memory (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_ra_meta_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct page* get_current_nat_page (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  scan_curseg_cache (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  scan_free_nid_bits (struct f2fs_sb_info*) ; 
 int scan_nat_page (struct f2fs_sb_info*,struct page*,int) ; 
 int /*<<< orphan*/  test_bit_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __f2fs_build_free_nids(struct f2fs_sb_info *sbi,
						bool sync, bool mount)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	int i = 0, ret;
	nid_t nid = nm_i->next_scan_nid;

	if (unlikely(nid >= nm_i->max_nid))
		nid = 0;

	/* Enough entries */
	if (nm_i->nid_cnt[FREE_NID] >= NAT_ENTRY_PER_BLOCK)
		return 0;

	if (!sync && !f2fs_available_free_memory(sbi, FREE_NIDS))
		return 0;

	if (!mount) {
		/* try to find free nids in free_nid_bitmap */
		scan_free_nid_bits(sbi);

		if (nm_i->nid_cnt[FREE_NID] >= NAT_ENTRY_PER_BLOCK)
			return 0;
	}

	/* readahead nat pages to be scanned */
	f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nid), FREE_NID_PAGES,
							META_NAT, true);

	down_read(&nm_i->nat_tree_lock);

	while (1) {
		if (!test_bit_le(NAT_BLOCK_OFFSET(nid),
						nm_i->nat_block_bitmap)) {
			struct page *page = get_current_nat_page(sbi, nid);

			if (IS_ERR(page)) {
				ret = PTR_ERR(page);
			} else {
				ret = scan_nat_page(sbi, page, nid);
				f2fs_put_page(page, 1);
			}

			if (ret) {
				up_read(&nm_i->nat_tree_lock);
				f2fs_bug_on(sbi, !mount);
				f2fs_err(sbi, "NAT is corrupt, run fsck to fix it");
				return ret;
			}
		}

		nid += (NAT_ENTRY_PER_BLOCK - (nid % NAT_ENTRY_PER_BLOCK));
		if (unlikely(nid >= nm_i->max_nid))
			nid = 0;

		if (++i >= FREE_NID_PAGES)
			break;
	}

	/* go to the next free nat pages to find free nids abundantly */
	nm_i->next_scan_nid = nid;

	/* find free nids from current sum_pages */
	scan_curseg_cache(sbi);

	up_read(&nm_i->nat_tree_lock);

	f2fs_ra_meta_pages(sbi, NAT_BLOCK_OFFSET(nm_i->next_scan_nid),
					nm_i->ra_nid_pages, META_NAT, false);

	return 0;
}