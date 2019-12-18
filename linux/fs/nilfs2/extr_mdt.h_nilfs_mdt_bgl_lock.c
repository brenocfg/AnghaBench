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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  mi_bgl; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/ * bgl_lock_ptr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline spinlock_t *
nilfs_mdt_bgl_lock(struct inode *inode, unsigned int block_group)
{
	return bgl_lock_ptr(NILFS_MDT(inode)->mi_bgl, block_group);
}