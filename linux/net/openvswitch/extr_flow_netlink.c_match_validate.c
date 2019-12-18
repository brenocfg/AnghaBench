#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct sw_flow_match {TYPE_9__* mask; TYPE_8__* key; } ;
struct TYPE_13__ {scalar_t__ type; } ;
struct TYPE_11__ {scalar_t__ src; } ;
struct TYPE_14__ {int proto; } ;
struct TYPE_15__ {TYPE_4__ eth; TYPE_2__ tp; TYPE_5__ ip; } ;
struct TYPE_18__ {TYPE_6__ key; } ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_10__ {scalar_t__ src; } ;
struct TYPE_16__ {scalar_t__ frag; scalar_t__ proto; } ;
struct TYPE_17__ {TYPE_3__ eth; TYPE_1__ tp; TYPE_7__ ip; } ;

/* Variables and functions */
 int ETH_P_ARP ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int ETH_P_NSH ; 
 int ETH_P_RARP ; 
 scalar_t__ IPPROTO_ICMP ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int NDISC_NEIGHBOUR_ADVERTISEMENT ; 
 int NDISC_NEIGHBOUR_SOLICITATION ; 
 scalar_t__ OVS_FRAG_TYPE_LATER ; 
 int OVS_KEY_ATTR_ARP ; 
 int OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4 ; 
 int OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6 ; 
 int OVS_KEY_ATTR_ETHERTYPE ; 
 int OVS_KEY_ATTR_ICMP ; 
 int OVS_KEY_ATTR_ICMPV6 ; 
 int OVS_KEY_ATTR_IN_PORT ; 
 int OVS_KEY_ATTR_IPV4 ; 
 int OVS_KEY_ATTR_IPV6 ; 
 int OVS_KEY_ATTR_MPLS ; 
 int OVS_KEY_ATTR_ND ; 
 int OVS_KEY_ATTR_NSH ; 
 int OVS_KEY_ATTR_SCTP ; 
 int OVS_KEY_ATTR_TCP ; 
 int OVS_KEY_ATTR_TCP_FLAGS ; 
 int OVS_KEY_ATTR_TUNNEL ; 
 int OVS_KEY_ATTR_UDP ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*,unsigned long long,unsigned long long) ; 
 scalar_t__ eth_p_mpls (scalar_t__) ; 
 scalar_t__ htons (int) ; 

__attribute__((used)) static bool match_validate(const struct sw_flow_match *match,
			   u64 key_attrs, u64 mask_attrs, bool log)
{
	u64 key_expected = 0;
	u64 mask_allowed = key_attrs;  /* At most allow all key attributes */

	/* The following mask attributes allowed only if they
	 * pass the validation tests. */
	mask_allowed &= ~((1 << OVS_KEY_ATTR_IPV4)
			| (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4)
			| (1 << OVS_KEY_ATTR_IPV6)
			| (1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6)
			| (1 << OVS_KEY_ATTR_TCP)
			| (1 << OVS_KEY_ATTR_TCP_FLAGS)
			| (1 << OVS_KEY_ATTR_UDP)
			| (1 << OVS_KEY_ATTR_SCTP)
			| (1 << OVS_KEY_ATTR_ICMP)
			| (1 << OVS_KEY_ATTR_ICMPV6)
			| (1 << OVS_KEY_ATTR_ARP)
			| (1 << OVS_KEY_ATTR_ND)
			| (1 << OVS_KEY_ATTR_MPLS)
			| (1 << OVS_KEY_ATTR_NSH));

	/* Always allowed mask fields. */
	mask_allowed |= ((1 << OVS_KEY_ATTR_TUNNEL)
		       | (1 << OVS_KEY_ATTR_IN_PORT)
		       | (1 << OVS_KEY_ATTR_ETHERTYPE));

	/* Check key attributes. */
	if (match->key->eth.type == htons(ETH_P_ARP)
			|| match->key->eth.type == htons(ETH_P_RARP)) {
		key_expected |= 1 << OVS_KEY_ATTR_ARP;
		if (match->mask && (match->mask->key.eth.type == htons(0xffff)))
			mask_allowed |= 1 << OVS_KEY_ATTR_ARP;
	}

	if (eth_p_mpls(match->key->eth.type)) {
		key_expected |= 1 << OVS_KEY_ATTR_MPLS;
		if (match->mask && (match->mask->key.eth.type == htons(0xffff)))
			mask_allowed |= 1 << OVS_KEY_ATTR_MPLS;
	}

	if (match->key->eth.type == htons(ETH_P_IP)) {
		key_expected |= 1 << OVS_KEY_ATTR_IPV4;
		if (match->mask && match->mask->key.eth.type == htons(0xffff)) {
			mask_allowed |= 1 << OVS_KEY_ATTR_IPV4;
			mask_allowed |= 1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV4;
		}

		if (match->key->ip.frag != OVS_FRAG_TYPE_LATER) {
			if (match->key->ip.proto == IPPROTO_UDP) {
				key_expected |= 1 << OVS_KEY_ATTR_UDP;
				if (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_UDP;
			}

			if (match->key->ip.proto == IPPROTO_SCTP) {
				key_expected |= 1 << OVS_KEY_ATTR_SCTP;
				if (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_SCTP;
			}

			if (match->key->ip.proto == IPPROTO_TCP) {
				key_expected |= 1 << OVS_KEY_ATTR_TCP;
				key_expected |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				if (match->mask && (match->mask->key.ip.proto == 0xff)) {
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP;
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				}
			}

			if (match->key->ip.proto == IPPROTO_ICMP) {
				key_expected |= 1 << OVS_KEY_ATTR_ICMP;
				if (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_ICMP;
			}
		}
	}

	if (match->key->eth.type == htons(ETH_P_IPV6)) {
		key_expected |= 1 << OVS_KEY_ATTR_IPV6;
		if (match->mask && match->mask->key.eth.type == htons(0xffff)) {
			mask_allowed |= 1 << OVS_KEY_ATTR_IPV6;
			mask_allowed |= 1 << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6;
		}

		if (match->key->ip.frag != OVS_FRAG_TYPE_LATER) {
			if (match->key->ip.proto == IPPROTO_UDP) {
				key_expected |= 1 << OVS_KEY_ATTR_UDP;
				if (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_UDP;
			}

			if (match->key->ip.proto == IPPROTO_SCTP) {
				key_expected |= 1 << OVS_KEY_ATTR_SCTP;
				if (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_SCTP;
			}

			if (match->key->ip.proto == IPPROTO_TCP) {
				key_expected |= 1 << OVS_KEY_ATTR_TCP;
				key_expected |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				if (match->mask && (match->mask->key.ip.proto == 0xff)) {
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP;
					mask_allowed |= 1 << OVS_KEY_ATTR_TCP_FLAGS;
				}
			}

			if (match->key->ip.proto == IPPROTO_ICMPV6) {
				key_expected |= 1 << OVS_KEY_ATTR_ICMPV6;
				if (match->mask && (match->mask->key.ip.proto == 0xff))
					mask_allowed |= 1 << OVS_KEY_ATTR_ICMPV6;

				if (match->key->tp.src ==
						htons(NDISC_NEIGHBOUR_SOLICITATION) ||
				    match->key->tp.src == htons(NDISC_NEIGHBOUR_ADVERTISEMENT)) {
					key_expected |= 1 << OVS_KEY_ATTR_ND;
					/* Original direction conntrack tuple
					 * uses the same space as the ND fields
					 * in the key, so both are not allowed
					 * at the same time.
					 */
					mask_allowed &= ~(1ULL << OVS_KEY_ATTR_CT_ORIG_TUPLE_IPV6);
					if (match->mask && (match->mask->key.tp.src == htons(0xff)))
						mask_allowed |= 1 << OVS_KEY_ATTR_ND;
				}
			}
		}
	}

	if (match->key->eth.type == htons(ETH_P_NSH)) {
		key_expected |= 1 << OVS_KEY_ATTR_NSH;
		if (match->mask &&
		    match->mask->key.eth.type == htons(0xffff)) {
			mask_allowed |= 1 << OVS_KEY_ATTR_NSH;
		}
	}

	if ((key_attrs & key_expected) != key_expected) {
		/* Key attributes check failed. */
		OVS_NLERR(log, "Missing key (keys=%llx, expected=%llx)",
			  (unsigned long long)key_attrs,
			  (unsigned long long)key_expected);
		return false;
	}

	if ((mask_attrs & mask_allowed) != mask_attrs) {
		/* Mask attributes check failed. */
		OVS_NLERR(log, "Unexpected mask (mask=%llx, allowed=%llx)",
			  (unsigned long long)mask_attrs,
			  (unsigned long long)mask_allowed);
		return false;
	}

	return true;
}