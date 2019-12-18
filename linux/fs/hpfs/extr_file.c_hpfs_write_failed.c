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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  hpfs_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_truncate (struct inode*) ; 
 int /*<<< orphan*/  hpfs_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 

__attribute__((used)) static void hpfs_write_failed(struct address_space *mapping, loff_t to)
{
	struct inode *inode = mapping->host;

	hpfs_lock(inode->i_sb);

	if (to > inode->i_size) {
		truncate_pagecache(inode, inode->i_size);
		hpfs_truncate(inode);
	}

	hpfs_unlock(inode->i_sb);
}