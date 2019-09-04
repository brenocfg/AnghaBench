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
struct ext4_inode_info {int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_wait_dax_page(struct ext4_inode_info *ei)
{
	up_write(&ei->i_mmap_sem);
	schedule();
	down_write(&ei->i_mmap_sem);
}