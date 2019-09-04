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
struct inode {scalar_t__ i_size; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  pagecache_isize_extended (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 

void truncate_setsize(struct inode *inode, loff_t newsize)
{
	loff_t oldsize = inode->i_size;

	i_size_write(inode, newsize);
	if (newsize > oldsize)
		pagecache_isize_extended(inode, oldsize, newsize);
	truncate_pagecache(inode, newsize);
}