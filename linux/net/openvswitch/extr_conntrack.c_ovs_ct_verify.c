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
struct ovs_net {int xt_label; } ;
struct net {int dummy; } ;
typedef  enum ovs_key_attr { ____Placeholder_ovs_key_attr } ovs_key_attr ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_LABELS ; 
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_MARK ; 
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_ZONES ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int OVS_KEY_ATTR_CT_LABELS ; 
 int OVS_KEY_ATTR_CT_MARK ; 
 int OVS_KEY_ATTR_CT_STATE ; 
 int OVS_KEY_ATTR_CT_ZONE ; 
 struct ovs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_net_id ; 

bool ovs_ct_verify(struct net *net, enum ovs_key_attr attr)
{
	if (attr == OVS_KEY_ATTR_CT_STATE)
		return true;
	if (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    attr == OVS_KEY_ATTR_CT_ZONE)
		return true;
	if (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) &&
	    attr == OVS_KEY_ATTR_CT_MARK)
		return true;
	if (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    attr == OVS_KEY_ATTR_CT_LABELS) {
		struct ovs_net *ovs_net = net_generic(net, ovs_net_id);

		return ovs_net->xt_label;
	}

	return false;
}