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
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

size_t ovs_tun_key_attr_size(void)
{
	/* Whenever adding new OVS_TUNNEL_KEY_ FIELDS, we should consider
	 * updating this function.
	 */
	return    nla_total_size_64bit(8) /* OVS_TUNNEL_KEY_ATTR_ID */
		+ nla_total_size(16)   /* OVS_TUNNEL_KEY_ATTR_IPV[46]_SRC */
		+ nla_total_size(16)   /* OVS_TUNNEL_KEY_ATTR_IPV[46]_DST */
		+ nla_total_size(1)    /* OVS_TUNNEL_KEY_ATTR_TOS */
		+ nla_total_size(1)    /* OVS_TUNNEL_KEY_ATTR_TTL */
		+ nla_total_size(0)    /* OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT */
		+ nla_total_size(0)    /* OVS_TUNNEL_KEY_ATTR_CSUM */
		+ nla_total_size(0)    /* OVS_TUNNEL_KEY_ATTR_OAM */
		+ nla_total_size(256)  /* OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS */
		/* OVS_TUNNEL_KEY_ATTR_VXLAN_OPTS and
		 * OVS_TUNNEL_KEY_ATTR_ERSPAN_OPTS is mutually exclusive with
		 * OVS_TUNNEL_KEY_ATTR_GENEVE_OPTS and covered by it.
		 */
		+ nla_total_size(2)    /* OVS_TUNNEL_KEY_ATTR_TP_SRC */
		+ nla_total_size(2);   /* OVS_TUNNEL_KEY_ATTR_TP_DST */
}