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
struct xt_hashlimit_htable {int /*<<< orphan*/  count; } ;
struct dsthash_ent {int /*<<< orphan*/  rcu; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsthash_free_rcu ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
dsthash_free(struct xt_hashlimit_htable *ht, struct dsthash_ent *ent)
{
	hlist_del_rcu(&ent->node);
	call_rcu(&ent->rcu, dsthash_free_rcu);
	ht->count--;
}