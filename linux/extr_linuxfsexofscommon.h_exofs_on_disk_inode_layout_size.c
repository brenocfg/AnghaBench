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
struct exofs_on_disk_inode_layout {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static inline size_t exofs_on_disk_inode_layout_size(unsigned max_devs)
{
	return sizeof(struct exofs_on_disk_inode_layout) +
		max_devs * sizeof(__le32);
}