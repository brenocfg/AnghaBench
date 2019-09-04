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
typedef  int /*<<< orphan*/  u64 ;
struct squashfs_cache_entry {int error; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  squashfs_cache_put (struct squashfs_cache_entry*) ; 
 int /*<<< orphan*/  squashfs_copy_cache (struct page*,struct squashfs_cache_entry*,int,int /*<<< orphan*/ ) ; 
 struct squashfs_cache_entry* squashfs_get_datablock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int squashfs_readpage_block(struct page *page, u64 block, int bsize, int expected)
{
	struct inode *i = page->mapping->host;
	struct squashfs_cache_entry *buffer = squashfs_get_datablock(i->i_sb,
		block, bsize);
	int res = buffer->error;

	if (res)
		ERROR("Unable to read page, block %llx, size %x\n", block,
			bsize);
	else
		squashfs_copy_cache(page, buffer, expected, 0);

	squashfs_cache_put(buffer);
	return res;
}