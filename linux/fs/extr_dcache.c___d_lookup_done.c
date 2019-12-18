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
struct hlist_bl_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_alias; int /*<<< orphan*/  d_in_lookup_hash; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct dentry {int /*<<< orphan*/  d_lru; TYPE_2__ d_u; int /*<<< orphan*/ * d_wait; int /*<<< orphan*/  d_flags; TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_PAR_LOOKUP ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __hlist_bl_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_bl_lock (struct hlist_bl_head*) ; 
 int /*<<< orphan*/  hlist_bl_unlock (struct hlist_bl_head*) ; 
 struct hlist_bl_head* in_lookup_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void __d_lookup_done(struct dentry *dentry)
{
	struct hlist_bl_head *b = in_lookup_hash(dentry->d_parent,
						 dentry->d_name.hash);
	hlist_bl_lock(b);
	dentry->d_flags &= ~DCACHE_PAR_LOOKUP;
	__hlist_bl_del(&dentry->d_u.d_in_lookup_hash);
	wake_up_all(dentry->d_wait);
	dentry->d_wait = NULL;
	hlist_bl_unlock(b);
	INIT_HLIST_NODE(&dentry->d_u.d_alias);
	INIT_LIST_HEAD(&dentry->d_lru);
}