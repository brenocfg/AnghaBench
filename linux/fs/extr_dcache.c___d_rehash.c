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
struct hlist_bl_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct dentry {int /*<<< orphan*/  d_hash; TYPE_1__ d_name; } ;

/* Variables and functions */
 struct hlist_bl_head* d_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_bl_add_head_rcu (int /*<<< orphan*/ *,struct hlist_bl_head*) ; 
 int /*<<< orphan*/  hlist_bl_lock (struct hlist_bl_head*) ; 
 int /*<<< orphan*/  hlist_bl_unlock (struct hlist_bl_head*) ; 

__attribute__((used)) static void __d_rehash(struct dentry *entry)
{
	struct hlist_bl_head *b = d_hash(entry->d_name.hash);

	hlist_bl_lock(b);
	hlist_bl_add_head_rcu(&entry->d_hash, b);
	hlist_bl_unlock(b);
}