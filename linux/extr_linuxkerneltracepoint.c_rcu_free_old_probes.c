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
struct rcu_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_srcu (int /*<<< orphan*/ *,struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcu_free_old_probes ; 
 int /*<<< orphan*/  tracepoint_srcu ; 

__attribute__((used)) static void rcu_free_old_probes(struct rcu_head *head)
{
	call_srcu(&tracepoint_srcu, head, srcu_free_old_probes);
}