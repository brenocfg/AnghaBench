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
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 unsigned int cmpxchg (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void inode_set_flags(struct inode *inode, unsigned int flags,
		     unsigned int mask)
{
	unsigned int old_flags, new_flags;

	WARN_ON_ONCE(flags & ~mask);
	do {
		old_flags = READ_ONCE(inode->i_flags);
		new_flags = (old_flags & ~mask) | flags;
	} while (unlikely(cmpxchg(&inode->i_flags, old_flags,
				  new_flags) != old_flags));
}