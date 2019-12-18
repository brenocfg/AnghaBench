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
struct flow_dissector_key {int dummy; } ;
struct flow_dissector {int dummy; } ;
struct fl_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ARP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CT ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CVLAN ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_OPTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_PORTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ICMP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int FLOW_DISSECTOR_KEY_MAX ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_META ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_MPLS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_TCP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 scalar_t__ FL_KEY_IS_MASKED (struct fl_flow_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FL_KEY_SET (struct flow_dissector_key*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FL_KEY_SET_IF_MASKED (struct fl_flow_key*,struct flow_dissector_key*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp ; 
 int /*<<< orphan*/  basic ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  ct ; 
 int /*<<< orphan*/  cvlan ; 
 int /*<<< orphan*/  enc_control ; 
 int /*<<< orphan*/  enc_ip ; 
 int /*<<< orphan*/  enc_ipv4 ; 
 int /*<<< orphan*/  enc_ipv6 ; 
 int /*<<< orphan*/  enc_key_id ; 
 int /*<<< orphan*/  enc_opts ; 
 int /*<<< orphan*/  enc_tp ; 
 int /*<<< orphan*/  eth ; 
 int /*<<< orphan*/  icmp ; 
 int /*<<< orphan*/  ip ; 
 int /*<<< orphan*/  ipv4 ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  meta ; 
 int /*<<< orphan*/  mpls ; 
 int /*<<< orphan*/  skb_flow_dissector_init (struct flow_dissector*,struct flow_dissector_key*,size_t) ; 
 int /*<<< orphan*/  tcp ; 
 int /*<<< orphan*/  tp ; 
 int /*<<< orphan*/  tp_max ; 
 int /*<<< orphan*/  tp_min ; 
 int /*<<< orphan*/  vlan ; 

__attribute__((used)) static void fl_init_dissector(struct flow_dissector *dissector,
			      struct fl_flow_key *mask)
{
	struct flow_dissector_key keys[FLOW_DISSECTOR_KEY_MAX];
	size_t cnt = 0;

	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_META, meta);
	FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_CONTROL, control);
	FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_BASIC, basic);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ETH_ADDRS, eth);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_IPV4_ADDRS, ipv4);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_IPV6_ADDRS, ipv6);
	if (FL_KEY_IS_MASKED(mask, tp) ||
	    FL_KEY_IS_MASKED(mask, tp_min) || FL_KEY_IS_MASKED(mask, tp_max))
		FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_PORTS, tp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_IP, ip);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_TCP, tcp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ICMP, icmp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ARP, arp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_MPLS, mpls);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_VLAN, vlan);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_CVLAN, cvlan);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_KEYID, enc_key_id);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS, enc_ipv4);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS, enc_ipv6);
	if (FL_KEY_IS_MASKED(mask, enc_ipv4) ||
	    FL_KEY_IS_MASKED(mask, enc_ipv6))
		FL_KEY_SET(keys, cnt, FLOW_DISSECTOR_KEY_ENC_CONTROL,
			   enc_control);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_PORTS, enc_tp);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_IP, enc_ip);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_ENC_OPTS, enc_opts);
	FL_KEY_SET_IF_MASKED(mask, keys, cnt,
			     FLOW_DISSECTOR_KEY_CT, ct);

	skb_flow_dissector_init(dissector, keys, cnt);
}