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
struct pernet_operations {int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister_pernet_operations (struct pernet_operations*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_generic_ids ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static void unregister_pernet_operations(struct pernet_operations *ops)
{
	__unregister_pernet_operations(ops);
	rcu_barrier();
	if (ops->id)
		ida_free(&net_generic_ids, *ops->id);
}