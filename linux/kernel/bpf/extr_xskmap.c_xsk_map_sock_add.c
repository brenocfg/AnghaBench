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
struct xsk_map_node {int /*<<< orphan*/  node; } ;
struct xdp_sock {int /*<<< orphan*/  map_list_lock; int /*<<< orphan*/  map_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xsk_map_sock_add(struct xdp_sock *xs, struct xsk_map_node *node)
{
	spin_lock_bh(&xs->map_list_lock);
	list_add_tail(&node->node, &xs->map_list);
	spin_unlock_bh(&xs->map_list_lock);
}