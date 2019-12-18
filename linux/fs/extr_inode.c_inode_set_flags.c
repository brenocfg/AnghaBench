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
struct inode {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

void inode_set_flags(struct inode *inode, unsigned int flags,
		     unsigned int mask)
{
	WARN_ON_ONCE(flags & ~mask);
	set_mask_bits(&inode->i_flags, mask, flags);
}