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
struct srcu_struct {int dummy; } ;
struct rcu_synchronize {int /*<<< orphan*/  head; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_srcu (struct srcu_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_rcu_head_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rcu_head_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeme_after_rcu ; 

void synchronize_srcu(struct srcu_struct *ssp)
{
	struct rcu_synchronize rs;

	init_rcu_head_on_stack(&rs.head);
	init_completion(&rs.completion);
	call_srcu(ssp, &rs.head, wakeme_after_rcu);
	wait_for_completion(&rs.completion);
	destroy_rcu_head_on_stack(&rs.head);
}