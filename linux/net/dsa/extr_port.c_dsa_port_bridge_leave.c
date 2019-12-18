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
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/ * bridge_dev; int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct dsa_notifier_bridge_info {struct net_device* br; int /*<<< orphan*/  port; int /*<<< orphan*/  sw_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_FORWARDING ; 
 int /*<<< orphan*/  DSA_NOTIFIER_BRIDGE_LEAVE ; 
 int /*<<< orphan*/  dsa_port_bridge_flags (struct dsa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsa_port_notify (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_notifier_bridge_info*) ; 
 int /*<<< orphan*/  dsa_port_set_state_now (struct dsa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void dsa_port_bridge_leave(struct dsa_port *dp, struct net_device *br)
{
	struct dsa_notifier_bridge_info info = {
		.sw_index = dp->ds->index,
		.port = dp->index,
		.br = br,
	};
	int err;

	/* Here the port is already unbridged. Reflect the current configuration
	 * so that drivers can program their chips accordingly.
	 */
	dp->bridge_dev = NULL;

	err = dsa_port_notify(dp, DSA_NOTIFIER_BRIDGE_LEAVE, &info);
	if (err)
		pr_err("DSA: failed to notify DSA_NOTIFIER_BRIDGE_LEAVE\n");

	/* Port is leaving the bridge, disable flooding */
	dsa_port_bridge_flags(dp, 0, NULL);

	/* Port left the bridge, put in BR_STATE_DISABLED by the bridge layer,
	 * so allow it to be in BR_STATE_FORWARDING to be kept functional
	 */
	dsa_port_set_state_now(dp, BR_STATE_FORWARDING);
}