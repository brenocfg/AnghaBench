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
struct tipc_node {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_node_delete_from_list (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  trace_tipc_node_delete (struct tipc_node*,int,char*) ; 

__attribute__((used)) static void tipc_node_delete(struct tipc_node *node)
{
	trace_tipc_node_delete(node, true, " ");
	tipc_node_delete_from_list(node);

	del_timer_sync(&node->timer);
	tipc_node_put(node);
}