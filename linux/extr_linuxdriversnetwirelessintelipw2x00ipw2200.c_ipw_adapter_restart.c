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
struct ipw_priv {int status; TYPE_1__* assoc_network; } ;
struct TYPE_2__ {int capability; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int STATUS_RF_KILL_MASK ; 
 int WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  ipw_down (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_remove_current_network (struct ipw_priv*) ; 
 scalar_t__ ipw_up (struct ipw_priv*) ; 

__attribute__((used)) static void ipw_adapter_restart(void *adapter)
{
	struct ipw_priv *priv = adapter;

	if (priv->status & STATUS_RF_KILL_MASK)
		return;

	ipw_down(priv);

	if (priv->assoc_network &&
	    (priv->assoc_network->capability & WLAN_CAPABILITY_IBSS))
		ipw_remove_current_network(priv);

	if (ipw_up(priv)) {
		IPW_ERROR("Failed to up device\n");
		return;
	}
}