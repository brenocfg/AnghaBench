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
struct pernet_operations {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  exit_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/  init_net_initialized ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_exit_list ; 
 int /*<<< orphan*/  ops_exit_list (struct pernet_operations*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ops_free_list (struct pernet_operations*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ops_pre_exit_list (struct pernet_operations*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void __unregister_pernet_operations(struct pernet_operations *ops)
{
	if (!init_net_initialized) {
		list_del(&ops->list);
	} else {
		LIST_HEAD(net_exit_list);
		list_add(&init_net.exit_list, &net_exit_list);
		ops_pre_exit_list(ops, &net_exit_list);
		synchronize_rcu();
		ops_exit_list(ops, &net_exit_list);
		ops_free_list(ops, &net_exit_list);
	}
}