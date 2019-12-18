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
struct dsa_port {struct net_device* bridge_dev; int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct dsa_notifier_bridge_info {struct net_device* br; int /*<<< orphan*/  port; int /*<<< orphan*/  sw_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int BR_FLOOD ; 
 int BR_MCAST_FLOOD ; 
 int /*<<< orphan*/  DSA_NOTIFIER_BRIDGE_JOIN ; 
 int dsa_port_bridge_flags (struct dsa_port*,int,int /*<<< orphan*/ *) ; 
 int dsa_port_notify (struct dsa_port*,int /*<<< orphan*/ ,struct dsa_notifier_bridge_info*) ; 

int dsa_port_bridge_join(struct dsa_port *dp, struct net_device *br)
{
	struct dsa_notifier_bridge_info info = {
		.sw_index = dp->ds->index,
		.port = dp->index,
		.br = br,
	};
	int err;

	/* Set the flooding mode before joining the port in the switch */
	err = dsa_port_bridge_flags(dp, BR_FLOOD | BR_MCAST_FLOOD, NULL);
	if (err)
		return err;

	/* Here the interface is already bridged. Reflect the current
	 * configuration so that drivers can program their chips accordingly.
	 */
	dp->bridge_dev = br;

	err = dsa_port_notify(dp, DSA_NOTIFIER_BRIDGE_JOIN, &info);

	/* The bridging is rolled back on error */
	if (err) {
		dsa_port_bridge_flags(dp, 0, NULL);
		dp->bridge_dev = NULL;
	}

	return err;
}