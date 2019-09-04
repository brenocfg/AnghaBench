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
struct TYPE_2__ {unsigned long flags; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_LAYOUTCOMMITTING ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnfs_clear_layoutcommitting(struct inode *inode)
{
	unsigned long *bitlock = &NFS_I(inode)->flags;

	clear_bit_unlock(NFS_INO_LAYOUTCOMMITTING, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, NFS_INO_LAYOUTCOMMITTING);
}