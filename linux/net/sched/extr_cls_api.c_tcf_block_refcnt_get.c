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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_block {int /*<<< orphan*/  refcnt; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct tcf_block* tcf_block_lookup (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tcf_block *tcf_block_refcnt_get(struct net *net, u32 block_index)
{
	struct tcf_block *block;

	rcu_read_lock();
	block = tcf_block_lookup(net, block_index);
	if (block && !refcount_inc_not_zero(&block->refcnt))
		block = NULL;
	rcu_read_unlock();

	return block;
}