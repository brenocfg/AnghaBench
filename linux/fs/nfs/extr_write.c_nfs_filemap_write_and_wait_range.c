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
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int filemap_write_and_wait_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pnfs_sync_inode (int /*<<< orphan*/ ,int) ; 

int nfs_filemap_write_and_wait_range(struct address_space *mapping,
		loff_t lstart, loff_t lend)
{
	int ret;

	ret = filemap_write_and_wait_range(mapping, lstart, lend);
	if (ret == 0)
		ret = pnfs_sync_inode(mapping->host, true);
	return ret;
}