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
struct super_block {int /*<<< orphan*/  destroy_work; int /*<<< orphan*/  s_shrink; int /*<<< orphan*/  s_subtype; int /*<<< orphan*/  s_user_ns; int /*<<< orphan*/  s_inode_lru; int /*<<< orphan*/  s_dentry_lru; int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_super_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_prealloced_shrinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_lru_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_sb_free (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_unused_super(struct super_block *s)
{
	if (!s)
		return;
	up_write(&s->s_umount);
	list_lru_destroy(&s->s_dentry_lru);
	list_lru_destroy(&s->s_inode_lru);
	security_sb_free(s);
	put_user_ns(s->s_user_ns);
	kfree(s->s_subtype);
	free_prealloced_shrinker(&s->s_shrink);
	/* no delays needed */
	destroy_super_work(&s->destroy_work);
}