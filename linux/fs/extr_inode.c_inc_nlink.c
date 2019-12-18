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
struct inode {scalar_t__ i_nlink; int i_state; int /*<<< orphan*/  __i_nlink; TYPE_1__* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_remove_count; } ;

/* Variables and functions */
 int I_LINKABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void inc_nlink(struct inode *inode)
{
	if (unlikely(inode->i_nlink == 0)) {
		WARN_ON(!(inode->i_state & I_LINKABLE));
		atomic_long_dec(&inode->i_sb->s_remove_count);
	}

	inode->__i_nlink++;
}