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
struct super_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static inline void reiserfs_cond_resched(struct super_block *s)
{
	if (need_resched()) {
		int depth;

		depth = reiserfs_write_unlock_nested(s);
		schedule();
		reiserfs_write_lock_nested(s, depth);
	}
}