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
struct swap_info_struct {int /*<<< orphan*/  bdev; } ;
struct swap_extent {int start_page; int start_block; int nr_pages; } ;
typedef  int sector_t ;
typedef  int pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int PAGE_SHIFT ; 
 scalar_t__ blkdev_issue_discard (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct swap_extent* next_se (struct swap_extent*) ; 
 struct swap_extent* offset_to_swap_extent (struct swap_info_struct*,int) ; 

__attribute__((used)) static void discard_swap_cluster(struct swap_info_struct *si,
				 pgoff_t start_page, pgoff_t nr_pages)
{
	struct swap_extent *se = offset_to_swap_extent(si, start_page);

	while (nr_pages) {
		pgoff_t offset = start_page - se->start_page;
		sector_t start_block = se->start_block + offset;
		sector_t nr_blocks = se->nr_pages - offset;

		if (nr_blocks > nr_pages)
			nr_blocks = nr_pages;
		start_page += nr_blocks;
		nr_pages -= nr_blocks;

		start_block <<= PAGE_SHIFT - 9;
		nr_blocks <<= PAGE_SHIFT - 9;
		if (blkdev_issue_discard(si->bdev, start_block,
					nr_blocks, GFP_NOIO, 0))
			break;

		se = next_se(se);
	}
}