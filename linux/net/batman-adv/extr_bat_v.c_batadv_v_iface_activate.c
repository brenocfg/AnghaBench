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
struct batadv_hard_iface {scalar_t__ if_status; int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 scalar_t__ BATADV_IF_ACTIVE ; 
 scalar_t__ BATADV_IF_TO_BE_ACTIVATED ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_v_elp_iface_activate (struct batadv_hard_iface*,struct batadv_hard_iface*) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_v_iface_activate(struct batadv_hard_iface *hard_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(hard_iface->soft_iface);
	struct batadv_hard_iface *primary_if;

	primary_if = batadv_primary_if_get_selected(bat_priv);

	if (primary_if) {
		batadv_v_elp_iface_activate(primary_if, hard_iface);
		batadv_hardif_put(primary_if);
	}

	/* B.A.T.M.A.N. V does not use any queuing mechanism, therefore it can
	 * set the interface as ACTIVE right away, without any risk of race
	 * condition
	 */
	if (hard_iface->if_status == BATADV_IF_TO_BE_ACTIVATED)
		hard_iface->if_status = BATADV_IF_ACTIVE;
}