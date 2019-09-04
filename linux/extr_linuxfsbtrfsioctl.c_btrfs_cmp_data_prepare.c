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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct cmp_pages {int num_pages; int /*<<< orphan*/  dst_pages; int /*<<< orphan*/  src_pages; } ;

/* Variables and functions */
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  btrfs_cmp_data_free (struct cmp_pages*) ; 
 int gather_extent_pages (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_cmp_data_prepare(struct inode *src, u64 loff,
				  struct inode *dst, u64 dst_loff,
				  u64 len, struct cmp_pages *cmp)
{
	int ret;
	int num_pages = PAGE_ALIGN(len) >> PAGE_SHIFT;

	cmp->num_pages = num_pages;

	ret = gather_extent_pages(src, cmp->src_pages, num_pages, loff);
	if (ret)
		goto out;

	ret = gather_extent_pages(dst, cmp->dst_pages, num_pages, dst_loff);

out:
	if (ret)
		btrfs_cmp_data_free(cmp);
	return ret;
}