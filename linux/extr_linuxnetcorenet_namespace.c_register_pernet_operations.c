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
struct pernet_operations {int* id; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIN_PERNET_OPS_ID ; 
 int __register_pernet_operations (struct list_head*,struct pernet_operations*) ; 
 int ida_alloc_min (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_gen_ptrs ; 
 int /*<<< orphan*/  net_generic_ids ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static int register_pernet_operations(struct list_head *list,
				      struct pernet_operations *ops)
{
	int error;

	if (ops->id) {
		error = ida_alloc_min(&net_generic_ids, MIN_PERNET_OPS_ID,
				GFP_KERNEL);
		if (error < 0)
			return error;
		*ops->id = error;
		max_gen_ptrs = max(max_gen_ptrs, *ops->id + 1);
	}
	error = __register_pernet_operations(list, ops);
	if (error) {
		rcu_barrier();
		if (ops->id)
			ida_free(&net_generic_ids, *ops->id);
	}

	return error;
}