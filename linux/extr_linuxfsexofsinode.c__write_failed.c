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
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 

__attribute__((used)) static void _write_failed(struct inode *inode, loff_t to)
{
	if (to > inode->i_size)
		truncate_pagecache(inode, inode->i_size);
}