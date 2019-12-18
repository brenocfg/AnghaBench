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
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int ext4_mpage_readpages (struct address_space*,struct list_head*,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int
ext4_readpages(struct file *file, struct address_space *mapping,
		struct list_head *pages, unsigned nr_pages)
{
	struct inode *inode = mapping->host;

	/* If the file has inline data, no need to do readpages. */
	if (ext4_has_inline_data(inode))
		return 0;

	return ext4_mpage_readpages(mapping, pages, NULL, nr_pages, true);
}