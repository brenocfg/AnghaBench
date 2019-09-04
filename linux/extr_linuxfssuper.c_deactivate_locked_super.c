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
struct super_block {int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_inode_lru; int /*<<< orphan*/  s_dentry_lru; int /*<<< orphan*/  s_shrink; int /*<<< orphan*/  s_active; struct file_system_type* s_type; } ;
struct file_system_type {int /*<<< orphan*/  (* kill_sb ) (struct super_block*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleancache_invalidate_fs (struct super_block*) ; 
 int /*<<< orphan*/  list_lru_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 int /*<<< orphan*/  put_super (struct super_block*) ; 
 int /*<<< orphan*/  stub1 (struct super_block*) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void deactivate_locked_super(struct super_block *s)
{
	struct file_system_type *fs = s->s_type;
	if (atomic_dec_and_test(&s->s_active)) {
		cleancache_invalidate_fs(s);
		unregister_shrinker(&s->s_shrink);
		fs->kill_sb(s);

		/*
		 * Since list_lru_destroy() may sleep, we cannot call it from
		 * put_super(), where we hold the sb_lock. Therefore we destroy
		 * the lru lists right now.
		 */
		list_lru_destroy(&s->s_dentry_lru);
		list_lru_destroy(&s->s_inode_lru);

		put_filesystem(fs);
		put_super(s);
	} else {
		up_write(&s->s_umount);
	}
}