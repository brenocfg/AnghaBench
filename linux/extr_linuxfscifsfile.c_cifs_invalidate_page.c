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
struct page {TYPE_1__* mapping; } ;
struct cifsInodeInfo {int /*<<< orphan*/  vfs_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  cifs_fscache_invalidate_page (struct page*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cifs_invalidate_page(struct page *page, unsigned int offset,
				 unsigned int length)
{
	struct cifsInodeInfo *cifsi = CIFS_I(page->mapping->host);

	if (offset == 0 && length == PAGE_SIZE)
		cifs_fscache_invalidate_page(page, &cifsi->vfs_inode);
}