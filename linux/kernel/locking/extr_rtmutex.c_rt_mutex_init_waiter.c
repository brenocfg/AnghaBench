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
struct rt_mutex_waiter {int /*<<< orphan*/ * task; int /*<<< orphan*/  tree_entry; int /*<<< orphan*/  pi_tree_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_rt_mutex_init_waiter (struct rt_mutex_waiter*) ; 

void rt_mutex_init_waiter(struct rt_mutex_waiter *waiter)
{
	debug_rt_mutex_init_waiter(waiter);
	RB_CLEAR_NODE(&waiter->pi_tree_entry);
	RB_CLEAR_NODE(&waiter->tree_entry);
	waiter->task = NULL;
}