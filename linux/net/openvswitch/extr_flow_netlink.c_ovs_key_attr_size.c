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

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int OVS_KEY_ATTR_TUNNEL_INFO ; 
 size_t nla_total_size (int) ; 
 size_t ovs_nsh_key_attr_size () ; 
 size_t ovs_tun_key_attr_size () ; 

size_t ovs_key_attr_size(void)
{
	/* Whenever adding new OVS_KEY_ FIELDS, we should consider
	 * updating this function.
	 */
	BUILD_BUG_ON(OVS_KEY_ATTR_TUNNEL_INFO != 29);

	return    nla_total_size(4)   /* OVS_KEY_ATTR_PRIORITY */
		+ nla_total_size(0)   /* OVS_KEY_ATTR_TUNNEL */
		  + ovs_tun_key_attr_size()
		+ nla_total_size(4)   /* OVS_KEY_ATTR_IN_PORT */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_SKB_MARK */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_DP_HASH */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_RECIRC_ID */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_CT_STATE */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_CT_ZONE */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_CT_MARK */
		+ nla_total_size(16)  /* OVS_KEY_ATTR_CT_LABELS */
		+ nla_total_size(40)  /* OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6 */
		+ nla_total_size(0)   /* OVS_KEY_ATTR_NSH */
		  + ovs_nsh_key_attr_size()
		+ nla_total_size(12)  /* OVS_KEY_ATTR_ETHERNET */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_ETHERTYPE */
		+ nla_total_size(4)   /* OVS_KEY_ATTR_VLAN */
		+ nla_total_size(0)   /* OVS_KEY_ATTR_ENCAP */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_ETHERTYPE */
		+ nla_total_size(40)  /* OVS_KEY_ATTR_IPV6 */
		+ nla_total_size(2)   /* OVS_KEY_ATTR_ICMPV6 */
		+ nla_total_size(28); /* OVS_KEY_ATTR_ND */
}