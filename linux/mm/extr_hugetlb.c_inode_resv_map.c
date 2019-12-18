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
struct resv_map {int dummy; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;
struct inode {TYPE_1__ i_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct resv_map *inode_resv_map(struct inode *inode)
{
	/*
	 * At inode evict time, i_mapping may not point to the original
	 * address space within the inode.  This original address space
	 * contains the pointer to the resv_map.  So, always use the
	 * address space embedded within the inode.
	 * The VERY common case is inode->mapping == &inode->i_data but,
	 * this may not be true for device special inodes.
	 */
	return (struct resv_map *)(&inode->i_data)->private_data;
}