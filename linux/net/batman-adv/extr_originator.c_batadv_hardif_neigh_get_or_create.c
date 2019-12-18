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
struct batadv_hardif_neigh_node {int dummy; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 struct batadv_hardif_neigh_node* batadv_hardif_neigh_create (struct batadv_hard_iface*,int /*<<< orphan*/  const*,struct batadv_orig_node*) ; 
 struct batadv_hardif_neigh_node* batadv_hardif_neigh_get (struct batadv_hard_iface*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct batadv_hardif_neigh_node *
batadv_hardif_neigh_get_or_create(struct batadv_hard_iface *hard_iface,
				  const u8 *neigh_addr,
				  struct batadv_orig_node *orig_node)
{
	struct batadv_hardif_neigh_node *hardif_neigh;

	/* first check without locking to avoid the overhead */
	hardif_neigh = batadv_hardif_neigh_get(hard_iface, neigh_addr);
	if (hardif_neigh)
		return hardif_neigh;

	return batadv_hardif_neigh_create(hard_iface, neigh_addr, orig_node);
}