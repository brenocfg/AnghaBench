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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_ogm_packet {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
batadv_nc_update_nc_node(struct batadv_priv *bat_priv,
			 struct batadv_orig_node *orig_node,
			 struct batadv_orig_node *orig_neigh_node,
			 struct batadv_ogm_packet *ogm_packet,
			 int is_single_hop_neigh)
{
}