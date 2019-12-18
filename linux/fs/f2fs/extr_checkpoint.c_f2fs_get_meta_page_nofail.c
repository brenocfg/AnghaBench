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
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int DEFAULT_RETRY_IO_COUNT ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PTR_ERR (struct page*) ; 
 struct page* __get_meta_page (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_stop_checkpoint (struct f2fs_sb_info*,int) ; 

struct page *f2fs_get_meta_page_nofail(struct f2fs_sb_info *sbi, pgoff_t index)
{
	struct page *page;
	int count = 0;

retry:
	page = __get_meta_page(sbi, index, true);
	if (IS_ERR(page)) {
		if (PTR_ERR(page) == -EIO &&
				++count <= DEFAULT_RETRY_IO_COUNT)
			goto retry;
		f2fs_stop_checkpoint(sbi, false);
	}
	return page;
}