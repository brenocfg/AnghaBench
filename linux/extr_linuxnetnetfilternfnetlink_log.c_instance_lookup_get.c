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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nfulnl_instance {int /*<<< orphan*/  use; } ;
struct nfnl_log_net {int dummy; } ;

/* Variables and functions */
 struct nfulnl_instance* __instance_lookup (struct nfnl_log_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfulnl_instance *
instance_lookup_get(struct nfnl_log_net *log, u_int16_t group_num)
{
	struct nfulnl_instance *inst;

	rcu_read_lock_bh();
	inst = __instance_lookup(log, group_num);
	if (inst && !refcount_inc_not_zero(&inst->use))
		inst = NULL;
	rcu_read_unlock_bh();

	return inst;
}