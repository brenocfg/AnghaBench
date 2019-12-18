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
typedef  int /*<<< orphan*/  u8 ;
struct batadv_orig_node {int dummy; } ;
struct batadv_neigh_node {int dummy; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 struct batadv_neigh_node* batadv_neigh_node_create (struct batadv_orig_node*,struct batadv_hard_iface*,int /*<<< orphan*/  const*) ; 
 struct batadv_neigh_node* batadv_neigh_node_get (struct batadv_orig_node*,struct batadv_hard_iface*,int /*<<< orphan*/  const*) ; 

struct batadv_neigh_node *
batadv_neigh_node_get_or_create(struct batadv_orig_node *orig_node,
				struct batadv_hard_iface *hard_iface,
				const u8 *neigh_addr)
{
	struct batadv_neigh_node *neigh_node;

	/* first check without locking to avoid the overhead */
	neigh_node = batadv_neigh_node_get(orig_node, hard_iface, neigh_addr);
	if (neigh_node)
		return neigh_node;

	return batadv_neigh_node_create(orig_node, hard_iface, neigh_addr);
}