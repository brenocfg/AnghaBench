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
struct tcf_proto {int /*<<< orphan*/  destroy_ht_node; } ;
struct tcf_chain {struct tcf_block* block; } ;
struct tcf_block {int /*<<< orphan*/  proto_destroy_lock; int /*<<< orphan*/  proto_destroy_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_obj_hashfn (struct tcf_proto*) ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_proto_signal_destroying(struct tcf_chain *chain,
					struct tcf_proto *tp)
{
	struct tcf_block *block = chain->block;

	mutex_lock(&block->proto_destroy_lock);
	hash_add_rcu(block->proto_destroy_ht, &tp->destroy_ht_node,
		     destroy_obj_hashfn(tp));
	mutex_unlock(&block->proto_destroy_lock);
}