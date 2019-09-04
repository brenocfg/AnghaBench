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
struct net_device {TYPE_1__* ethtool_ops; } ;
struct ethtool_link_ksettings {int /*<<< orphan*/  cmd; } ;
struct ethtool_cmd {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int (* get_link_ksettings ) (struct net_device*,struct ethtool_link_ksettings*) ;int (* get_settings ) (struct net_device*,struct ethtool_link_ksettings*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 int /*<<< orphan*/  convert_legacy_settings_to_link_ksettings (struct ethtool_link_ksettings*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  memset (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct net_device*,struct ethtool_link_ksettings*) ; 
 int stub2 (struct net_device*,struct ethtool_link_ksettings*) ; 

int __ethtool_get_link_ksettings(struct net_device *dev,
				 struct ethtool_link_ksettings *link_ksettings)
{
	int err;
	struct ethtool_cmd cmd;

	ASSERT_RTNL();

	if (dev->ethtool_ops->get_link_ksettings) {
		memset(link_ksettings, 0, sizeof(*link_ksettings));
		return dev->ethtool_ops->get_link_ksettings(dev,
							    link_ksettings);
	}

	/* driver doesn't support %ethtool_link_ksettings API. revert to
	 * legacy %ethtool_cmd API, unless it's not supported either.
	 * TODO: remove when ethtool_ops::get_settings disappears internally
	 */
	if (!dev->ethtool_ops->get_settings)
		return -EOPNOTSUPP;

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd = ETHTOOL_GSET;
	err = dev->ethtool_ops->get_settings(dev, &cmd);
	if (err < 0)
		return err;

	/* we ignore deprecated fields transceiver/maxrxpkt/maxtxpkt
	 */
	convert_legacy_settings_to_link_ksettings(link_ksettings, &cmd);
	return err;
}