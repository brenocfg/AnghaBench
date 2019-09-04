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
struct inode {int i_state; TYPE_1__* i_sb; int /*<<< orphan*/  i_count; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int I_DIRTY_ALL ; 
 int I_FREEING ; 
 int I_SYNC ; 
 int I_WILL_FREE ; 
 int SB_ACTIVE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lru_list_add (struct inode*) ; 

void inode_add_lru(struct inode *inode)
{
	if (!(inode->i_state & (I_DIRTY_ALL | I_SYNC |
				I_FREEING | I_WILL_FREE)) &&
	    !atomic_read(&inode->i_count) && inode->i_sb->s_flags & SB_ACTIVE)
		inode_lru_list_add(inode);
}