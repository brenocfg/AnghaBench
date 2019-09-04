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
struct wiphy {int dummy; } ;
struct qtnf_vif {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct cfg80211_acl_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_set_mac_acl (struct qtnf_vif*,struct cfg80211_acl_data const*) ; 
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 

__attribute__((used)) static int qtnf_set_mac_acl(struct wiphy *wiphy,
			    struct net_device *dev,
			    const struct cfg80211_acl_data *params)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(dev);
	int ret;

	ret = qtnf_cmd_set_mac_acl(vif, params);
	if (ret)
		pr_err("%s: failed to set mac ACL ret=%d\n", dev->name, ret);

	return ret;
}