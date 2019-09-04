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
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (struct address_space*) ; 
 int /*<<< orphan*/  generic_block_bmap (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_data_block_bmap ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t f2fs_bmap(struct address_space *mapping, sector_t block)
{
	struct inode *inode = mapping->host;

	if (f2fs_has_inline_data(inode))
		return 0;

	/* make sure allocating whole blocks */
	if (mapping_tagged(mapping, PAGECACHE_TAG_DIRTY))
		filemap_write_and_wait(mapping);

	return generic_block_bmap(mapping, block, get_data_block_bmap);
}