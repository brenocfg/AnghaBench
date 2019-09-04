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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct compressed_bio {unsigned long nr_pages; int /*<<< orphan*/  mirror_num; struct page** compressed_pages; int /*<<< orphan*/  sums; } ;
struct btrfs_inode {int flags; } ;

/* Variables and functions */
 int BTRFS_INODE_NODATASUM ; 
 int EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  btrfs_csum_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_csum_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_print_data_csum_error (struct btrfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 

__attribute__((used)) static int check_compressed_csum(struct btrfs_inode *inode,
				 struct compressed_bio *cb,
				 u64 disk_start)
{
	int ret;
	struct page *page;
	unsigned long i;
	char *kaddr;
	u32 csum;
	u32 *cb_sum = &cb->sums;

	if (inode->flags & BTRFS_INODE_NODATASUM)
		return 0;

	for (i = 0; i < cb->nr_pages; i++) {
		page = cb->compressed_pages[i];
		csum = ~(u32)0;

		kaddr = kmap_atomic(page);
		csum = btrfs_csum_data(kaddr, csum, PAGE_SIZE);
		btrfs_csum_final(csum, (u8 *)&csum);
		kunmap_atomic(kaddr);

		if (csum != *cb_sum) {
			btrfs_print_data_csum_error(inode, disk_start, csum,
					*cb_sum, cb->mirror_num);
			ret = -EIO;
			goto fail;
		}
		cb_sum++;

	}
	ret = 0;
fail:
	return ret;
}