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
struct TYPE_4__ {int node; } ;
struct TYPE_3__ {int node; } ;
struct super_block {int /*<<< orphan*/  rcu; int /*<<< orphan*/  s_subtype; int /*<<< orphan*/  s_user_ns; int /*<<< orphan*/  s_mounts; TYPE_2__ s_inode_lru; TYPE_1__ s_dentry_lru; int /*<<< orphan*/  s_list; int /*<<< orphan*/  s_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_super_rcu ; 
 int /*<<< orphan*/  fscrypt_sb_free (struct super_block*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_sb_free (struct super_block*) ; 

__attribute__((used)) static void __put_super(struct super_block *s)
{
	if (!--s->s_count) {
		list_del_init(&s->s_list);
		WARN_ON(s->s_dentry_lru.node);
		WARN_ON(s->s_inode_lru.node);
		WARN_ON(!list_empty(&s->s_mounts));
		security_sb_free(s);
		fscrypt_sb_free(s);
		put_user_ns(s->s_user_ns);
		kfree(s->s_subtype);
		call_rcu(&s->rcu, destroy_super_rcu);
	}
}