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
typedef  int /*<<< orphan*/  udph ;
struct v6hdr {int dummy; } ;
struct udphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  protocol; } ;
struct gre_hdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  protocol; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  mpls_label ;
typedef  int /*<<< orphan*/  greh ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ADJ_ROOM_MAC ; 
 int /*<<< orphan*/  BPF_F_ADJ_ROOM_FIXED_GSO ; 
 int ETH_HLEN ; 
#define  ETH_OVER_UDP_PORT 135 
#define  ETH_P_MPLS_UC 134 
#define  ETH_P_TEB 133 
#define  IPPROTO_GRE 132 
#define  IPPROTO_IPIP 131 
#define  IPPROTO_IPV6 130 
#define  IPPROTO_UDP 129 
#define  MPLS_OVER_UDP_PORT 128 
 int TC_ACT_OK ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  bpf_ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ bpf_skb_adjust_room (struct __sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_skb_load_bytes (struct __sk_buff*,int,struct udphdr*,int) ; 

__attribute__((used)) static int decap_internal(struct __sk_buff *skb, int off, int len, char proto)
{
	char buf[sizeof(struct v6hdr)];
	struct gre_hdr greh;
	struct udphdr udph;
	int olen = len;

	switch (proto) {
	case IPPROTO_IPIP:
	case IPPROTO_IPV6:
		break;
	case IPPROTO_GRE:
		olen += sizeof(struct gre_hdr);
		if (bpf_skb_load_bytes(skb, off + len, &greh, sizeof(greh)) < 0)
			return TC_ACT_OK;
		switch (bpf_ntohs(greh.protocol)) {
		case ETH_P_MPLS_UC:
			olen += sizeof(mpls_label);
			break;
		case ETH_P_TEB:
			olen += ETH_HLEN;
			break;
		}
		break;
	case IPPROTO_UDP:
		olen += sizeof(struct udphdr);
		if (bpf_skb_load_bytes(skb, off + len, &udph, sizeof(udph)) < 0)
			return TC_ACT_OK;
		switch (bpf_ntohs(udph.dest)) {
		case MPLS_OVER_UDP_PORT:
			olen += sizeof(mpls_label);
			break;
		case ETH_OVER_UDP_PORT:
			olen += ETH_HLEN;
			break;
		}
		break;
	default:
		return TC_ACT_OK;
	}

	if (bpf_skb_adjust_room(skb, -olen, BPF_ADJ_ROOM_MAC,
				BPF_F_ADJ_ROOM_FIXED_GSO))
		return TC_ACT_SHOT;

	return TC_ACT_OK;
}