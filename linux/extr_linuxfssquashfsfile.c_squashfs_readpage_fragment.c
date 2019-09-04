#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct squashfs_cache_entry {int error; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  fragment_offset; int /*<<< orphan*/  fragment_size; int /*<<< orphan*/  fragment_block; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  squashfs_cache_put (struct squashfs_cache_entry*) ; 
 int /*<<< orphan*/  squashfs_copy_cache (struct page*,struct squashfs_cache_entry*,int,int /*<<< orphan*/ ) ; 
 struct squashfs_cache_entry* squashfs_get_fragment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* squashfs_i (struct inode*) ; 

__attribute__((used)) static int squashfs_readpage_fragment(struct page *page, int expected)
{
	struct inode *inode = page->mapping->host;
	struct squashfs_cache_entry *buffer = squashfs_get_fragment(inode->i_sb,
		squashfs_i(inode)->fragment_block,
		squashfs_i(inode)->fragment_size);
	int res = buffer->error;

	if (res)
		ERROR("Unable to read page, block %llx, size %x\n",
			squashfs_i(inode)->fragment_block,
			squashfs_i(inode)->fragment_size);
	else
		squashfs_copy_cache(page, buffer, expected,
			squashfs_i(inode)->fragment_offset);

	squashfs_cache_put(buffer);
	return res;
}