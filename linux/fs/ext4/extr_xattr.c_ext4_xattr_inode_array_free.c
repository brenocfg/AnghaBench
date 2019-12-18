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
struct ext4_xattr_inode_array {int count; int /*<<< orphan*/ * inodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ext4_xattr_inode_array*) ; 

void ext4_xattr_inode_array_free(struct ext4_xattr_inode_array *ea_inode_array)
{
	int idx;

	if (ea_inode_array == NULL)
		return;

	for (idx = 0; idx < ea_inode_array->count; ++idx)
		iput(ea_inode_array->inodes[idx]);
	kfree(ea_inode_array);
}