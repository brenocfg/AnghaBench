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
struct list_head {int dummy; } ;
struct audit_chunk {int /*<<< orphan*/  hash; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct list_head* chunk_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void insert_hash(struct audit_chunk *chunk)
{
	struct list_head *list;

	/*
	 * Make sure chunk is fully initialized before making it visible in the
	 * hash. Pairs with a data dependency barrier in READ_ONCE() in
	 * audit_tree_lookup().
	 */
	smp_wmb();
	WARN_ON_ONCE(!chunk->key);
	list = chunk_hash(chunk->key);
	list_add_rcu(&chunk->hash, list);
}