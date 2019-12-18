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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct dsa_port {struct dsa_port* cpu_dp; scalar_t__ bridge_dev; } ;
struct bridge_vlan_info {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  br_vlan_enabled (scalar_t__) ; 
 int br_vlan_get_info (scalar_t__,int /*<<< orphan*/ ,struct bridge_vlan_info*) ; 
 int dsa_port_vid_add (struct dsa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_vlan_rx_add_vid(struct net_device *dev, __be16 proto,
				     u16 vid)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct bridge_vlan_info info;
	int ret;

	/* Check for a possible bridge VLAN entry now since there is no
	 * need to emulate the switchdev prepare + commit phase.
	 */
	if (dp->bridge_dev) {
		if (!br_vlan_enabled(dp->bridge_dev))
			return 0;

		/* br_vlan_get_info() returns -EINVAL or -ENOENT if the
		 * device, respectively the VID is not found, returning
		 * 0 means success, which is a failure for us here.
		 */
		ret = br_vlan_get_info(dp->bridge_dev, vid, &info);
		if (ret == 0)
			return -EBUSY;
	}

	ret = dsa_port_vid_add(dp, vid, 0);
	if (ret)
		return ret;

	ret = dsa_port_vid_add(dp->cpu_dp, vid, 0);
	if (ret)
		return ret;

	return 0;
}