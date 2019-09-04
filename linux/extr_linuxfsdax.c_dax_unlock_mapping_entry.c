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
struct page {int /*<<< orphan*/  index; struct address_space* mapping; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_mapping_entry (struct address_space*,int /*<<< orphan*/ ) ; 

void dax_unlock_mapping_entry(struct page *page)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode = mapping->host;

	if (S_ISCHR(inode->i_mode))
		return;

	unlock_mapping_entry(mapping, page->index);
}