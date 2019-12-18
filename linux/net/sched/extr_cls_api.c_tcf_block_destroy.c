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
struct tcf_block {int /*<<< orphan*/  proto_destroy_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct tcf_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void tcf_block_destroy(struct tcf_block *block)
{
	mutex_destroy(&block->lock);
	mutex_destroy(&block->proto_destroy_lock);
	kfree_rcu(block, rcu);
}