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
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_sb_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_inode_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void inode_sb_list_del(struct inode *inode)
{
	if (!list_empty(&inode->i_sb_list)) {
		spin_lock(&inode->i_sb->s_inode_list_lock);
		list_del_init(&inode->i_sb_list);
		spin_unlock(&inode->i_sb->s_inode_list_lock);
	}
}