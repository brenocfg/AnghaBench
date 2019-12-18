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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  ceph_zero_partial_page (struct inode*,scalar_t__,scalar_t__) ; 
 scalar_t__ round_down (scalar_t__,scalar_t__) ; 
 scalar_t__ round_up (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ceph_zero_pagecache_range(struct inode *inode, loff_t offset,
				      loff_t length)
{
	loff_t nearly = round_up(offset, PAGE_SIZE);
	if (offset < nearly) {
		loff_t size = nearly - offset;
		if (length < size)
			size = length;
		ceph_zero_partial_page(inode, offset, size);
		offset += size;
		length -= size;
	}
	if (length >= PAGE_SIZE) {
		loff_t size = round_down(length, PAGE_SIZE);
		truncate_pagecache_range(inode, offset, offset + size - 1);
		offset += size;
		length -= size;
	}
	if (length)
		ceph_zero_partial_page(inode, offset, length);
}