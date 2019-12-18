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
struct nilfs_palloc_group_desc {int /*<<< orphan*/  pg_nfrees; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_palloc_entries_per_group (struct inode*) ; 
 unsigned long nilfs_palloc_groups_per_desc_block (struct inode*) ; 

__attribute__((used)) static void nilfs_palloc_desc_block_init(struct inode *inode,
					 struct buffer_head *bh, void *kaddr)
{
	struct nilfs_palloc_group_desc *desc = kaddr + bh_offset(bh);
	unsigned long n = nilfs_palloc_groups_per_desc_block(inode);
	__le32 nfrees;

	nfrees = cpu_to_le32(nilfs_palloc_entries_per_group(inode));
	while (n-- > 0) {
		desc->pg_nfrees = nfrees;
		desc++;
	}
}