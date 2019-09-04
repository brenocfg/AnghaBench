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
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct cramfs_sb_info {scalar_t__ linear_virt_addr; } ;

/* Variables and functions */
 int CRAMFS_BLK_DIRECT_PTR_SHIFT ; 
 int CRAMFS_BLK_FLAGS ; 
 int CRAMFS_BLK_FLAG_DIRECT_PTR ; 
 int CRAMFS_BLK_FLAG_UNCOMPRESSED ; 
 struct cramfs_sb_info* CRAMFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ OFFSET (struct inode*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int) ; 

__attribute__((used)) static u32 cramfs_get_block_range(struct inode *inode, u32 pgoff, u32 *pages)
{
	struct cramfs_sb_info *sbi = CRAMFS_SB(inode->i_sb);
	int i;
	u32 *blockptrs, first_block_addr;

	/*
	 * We can dereference memory directly here as this code may be
	 * reached only when there is a direct filesystem image mapping
	 * available in memory.
	 */
	blockptrs = (u32 *)(sbi->linear_virt_addr + OFFSET(inode) + pgoff * 4);
	first_block_addr = blockptrs[0] & ~CRAMFS_BLK_FLAGS;
	i = 0;
	do {
		u32 block_off = i * (PAGE_SIZE >> CRAMFS_BLK_DIRECT_PTR_SHIFT);
		u32 expect = (first_block_addr + block_off) |
			     CRAMFS_BLK_FLAG_DIRECT_PTR |
			     CRAMFS_BLK_FLAG_UNCOMPRESSED;
		if (blockptrs[i] != expect) {
			pr_debug("range: block %d/%d got %#x expects %#x\n",
				 pgoff+i, pgoff + *pages - 1,
				 blockptrs[i], expect);
			if (i == 0)
				return 0;
			break;
		}
	} while (++i < *pages);

	*pages = i;
	return first_block_addr << CRAMFS_BLK_DIRECT_PTR_SHIFT;
}