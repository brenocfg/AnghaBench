#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  frag; } ;
struct sw_flow_key {TYPE_1__ ip; } ;
struct sw_flow_actions {int dummy; } ;
struct ovs_key_ipv6 {int /*<<< orphan*/  ipv6_label; int /*<<< orphan*/  ipv6_frag; int /*<<< orphan*/  ipv6_proto; } ;
struct ovs_key_ipv4 {int /*<<< orphan*/  ipv4_frag; int /*<<< orphan*/  ipv4_proto; } ;
typedef  struct nlattr const nlattr ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_NSH ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ IS_ERR (struct nlattr const*) ; 
 int /*<<< orphan*/  MAC_PROTO_ETHERNET ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_SET_TO_MASKED ; 
#define  OVS_KEY_ATTR_CT_LABELS 140 
#define  OVS_KEY_ATTR_CT_MARK 139 
#define  OVS_KEY_ATTR_ETHERNET 138 
#define  OVS_KEY_ATTR_IPV4 137 
#define  OVS_KEY_ATTR_IPV6 136 
 int OVS_KEY_ATTR_MAX ; 
#define  OVS_KEY_ATTR_MPLS 135 
#define  OVS_KEY_ATTR_NSH 134 
#define  OVS_KEY_ATTR_PRIORITY 133 
#define  OVS_KEY_ATTR_SCTP 132 
#define  OVS_KEY_ATTR_SKB_MARK 131 
#define  OVS_KEY_ATTR_TCP 130 
#define  OVS_KEY_ATTR_TUNNEL 129 
#define  OVS_KEY_ATTR_UDP 128 
 int PTR_ERR (struct nlattr const*) ; 
 struct nlattr const* __add_action (struct sw_flow_actions**,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  add_nested_action_end (struct sw_flow_actions*,int) ; 
 int add_nested_action_start (struct sw_flow_actions**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_attr_len (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_p_mpls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 void* nla_data (struct nlattr const*) ; 
 size_t nla_len (struct nlattr const*) ; 
 size_t nla_total_size (size_t) ; 
 int nla_type (struct nlattr const*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 TYPE_2__* ovs_key_lens ; 
 int validate_and_copy_set_tun (struct nlattr const*,struct sw_flow_actions**,int) ; 
 int /*<<< orphan*/  validate_masked (void*,size_t) ; 
 int /*<<< orphan*/  validate_nsh (void*,int,int,int) ; 

__attribute__((used)) static int validate_set(const struct nlattr *a,
			const struct sw_flow_key *flow_key,
			struct sw_flow_actions **sfa, bool *skip_copy,
			u8 mac_proto, __be16 eth_type, bool masked, bool log)
{
	const struct nlattr *ovs_key = nla_data(a);
	int key_type = nla_type(ovs_key);
	size_t key_len;

	/* There can be only one key in a action */
	if (nla_total_size(nla_len(ovs_key)) != nla_len(a))
		return -EINVAL;

	key_len = nla_len(ovs_key);
	if (masked)
		key_len /= 2;

	if (key_type > OVS_KEY_ATTR_MAX ||
	    !check_attr_len(key_len, ovs_key_lens[key_type].len))
		return -EINVAL;

	if (masked && !validate_masked(nla_data(ovs_key), key_len))
		return -EINVAL;

	switch (key_type) {
	const struct ovs_key_ipv4 *ipv4_key;
	const struct ovs_key_ipv6 *ipv6_key;
	int err;

	case OVS_KEY_ATTR_PRIORITY:
	case OVS_KEY_ATTR_SKB_MARK:
	case OVS_KEY_ATTR_CT_MARK:
	case OVS_KEY_ATTR_CT_LABELS:
		break;

	case OVS_KEY_ATTR_ETHERNET:
		if (mac_proto != MAC_PROTO_ETHERNET)
			return -EINVAL;
		break;

	case OVS_KEY_ATTR_TUNNEL:
		if (masked)
			return -EINVAL; /* Masked tunnel set not supported. */

		*skip_copy = true;
		err = validate_and_copy_set_tun(a, sfa, log);
		if (err)
			return err;
		break;

	case OVS_KEY_ATTR_IPV4:
		if (eth_type != htons(ETH_P_IP))
			return -EINVAL;

		ipv4_key = nla_data(ovs_key);

		if (masked) {
			const struct ovs_key_ipv4 *mask = ipv4_key + 1;

			/* Non-writeable fields. */
			if (mask->ipv4_proto || mask->ipv4_frag)
				return -EINVAL;
		} else {
			if (ipv4_key->ipv4_proto != flow_key->ip.proto)
				return -EINVAL;

			if (ipv4_key->ipv4_frag != flow_key->ip.frag)
				return -EINVAL;
		}
		break;

	case OVS_KEY_ATTR_IPV6:
		if (eth_type != htons(ETH_P_IPV6))
			return -EINVAL;

		ipv6_key = nla_data(ovs_key);

		if (masked) {
			const struct ovs_key_ipv6 *mask = ipv6_key + 1;

			/* Non-writeable fields. */
			if (mask->ipv6_proto || mask->ipv6_frag)
				return -EINVAL;

			/* Invalid bits in the flow label mask? */
			if (ntohl(mask->ipv6_label) & 0xFFF00000)
				return -EINVAL;
		} else {
			if (ipv6_key->ipv6_proto != flow_key->ip.proto)
				return -EINVAL;

			if (ipv6_key->ipv6_frag != flow_key->ip.frag)
				return -EINVAL;
		}
		if (ntohl(ipv6_key->ipv6_label) & 0xFFF00000)
			return -EINVAL;

		break;

	case OVS_KEY_ATTR_TCP:
		if ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    flow_key->ip.proto != IPPROTO_TCP)
			return -EINVAL;

		break;

	case OVS_KEY_ATTR_UDP:
		if ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    flow_key->ip.proto != IPPROTO_UDP)
			return -EINVAL;

		break;

	case OVS_KEY_ATTR_MPLS:
		if (!eth_p_mpls(eth_type))
			return -EINVAL;
		break;

	case OVS_KEY_ATTR_SCTP:
		if ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    flow_key->ip.proto != IPPROTO_SCTP)
			return -EINVAL;

		break;

	case OVS_KEY_ATTR_NSH:
		if (eth_type != htons(ETH_P_NSH))
			return -EINVAL;
		if (!validate_nsh(nla_data(a), masked, false, log))
			return -EINVAL;
		break;

	default:
		return -EINVAL;
	}

	/* Convert non-masked non-tunnel set actions to masked set actions. */
	if (!masked && key_type != OVS_KEY_ATTR_TUNNEL) {
		int start, len = key_len * 2;
		struct nlattr *at;

		*skip_copy = true;

		start = add_nested_action_start(sfa,
						OVS_ACTION_ATTR_SET_TO_MASKED,
						log);
		if (start < 0)
			return start;

		at = __add_action(sfa, key_type, NULL, len, log);
		if (IS_ERR(at))
			return PTR_ERR(at);

		memcpy(nla_data(at), nla_data(ovs_key), key_len); /* Key. */
		memset(nla_data(at) + key_len, 0xff, key_len);    /* Mask. */
		/* Clear non-writeable bits from otherwise writeable fields. */
		if (key_type == OVS_KEY_ATTR_IPV6) {
			struct ovs_key_ipv6 *mask = nla_data(at) + key_len;

			mask->ipv6_label &= htonl(0x000FFFFF);
		}
		add_nested_action_end(*sfa, start);
	}

	return 0;
}