#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lock_class_key {int dummy; } ;
struct inode {int /*<<< orphan*/  i_rwsem; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int s_stack_depth; } ;

/* Variables and functions */
 TYPE_2__* OVL_I (struct inode*) ; 
 int OVL_MAX_NESTING ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 

__attribute__((used)) static inline void ovl_lockdep_annotate_inode_mutex_key(struct inode *inode)
{
#ifdef CONFIG_LOCKDEP
	static struct lock_class_key ovl_i_mutex_key[OVL_MAX_NESTING];
	static struct lock_class_key ovl_i_mutex_dir_key[OVL_MAX_NESTING];
	static struct lock_class_key ovl_i_lock_key[OVL_MAX_NESTING];

	int depth = inode->i_sb->s_stack_depth - 1;

	if (WARN_ON_ONCE(depth < 0 || depth >= OVL_MAX_NESTING))
		depth = 0;

	if (S_ISDIR(inode->i_mode))
		lockdep_set_class(&inode->i_rwsem, &ovl_i_mutex_dir_key[depth]);
	else
		lockdep_set_class(&inode->i_rwsem, &ovl_i_mutex_key[depth]);

	lockdep_set_class(&OVL_I(inode)->lock, &ovl_i_lock_key[depth]);
#endif
}