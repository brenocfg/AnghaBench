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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct sw_flow_key {TYPE_1__ eth; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4 ; 
 int OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6 ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_MAX ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int key_extract (struct sk_buff*,struct sw_flow_key*) ; 
 int ovs_nla_get_flow_metadata (struct net*,struct nlattr const**,int,struct sw_flow_key*,int) ; 
 int parse_flow_nlattrs (struct nlattr const*,struct nlattr const**,int*,int) ; 
 scalar_t__ sw_flow_key_is_nd (struct sw_flow_key*) ; 

int ovs_flow_key_extract_userspace(struct net *net, const struct nlattr *attr,
				   struct sk_buff *skb,
				   struct sw_flow_key *key, bool log)
{
	const struct nlattr *a[OVS_KEY_ATTR_MAX + 1];
	u64 attrs = 0;
	int err;

	err = parse_flow_nlattrs(attr, a, &attrs, log);
	if (err)
		return -EINVAL;

	/* Extract metadata from netlink attributes. */
	err = ovs_nla_get_flow_metadata(net, a, attrs, key, log);
	if (err)
		return err;

	/* key_extract assumes that skb->protocol is set-up for
	 * layer 3 packets which is the case for other callers,
	 * in particular packets received from the network stack.
	 * Here the correct value can be set from the metadata
	 * extracted above.
	 * For L2 packet key eth type would be zero. skb protocol
	 * would be set to correct value later during key-extact.
	 */

	skb->protocol = key->eth.type;
	err = key_extract(skb, key);
	if (err)
		return err;

	/* Check that we have conntrack original direction tuple metadata only
	 * for packets for which it makes sense.  Otherwise the key may be
	 * corrupted due to overlapping key fields.
	 */
	if (attrs & (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4) &&
	    key->eth.type != htons(ETH_P_IP))
		return -EINVAL;
	if (attrs & (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6) &&
	    (key->eth.type != htons(ETH_P_IPV6) ||
	     sw_flow_key_is_nd(key)))
		return -EINVAL;

	return 0;
}