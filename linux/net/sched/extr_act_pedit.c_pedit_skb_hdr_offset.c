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
struct sk_buff {int dummy; } ;
typedef  enum pedit_header_type { ____Placeholder_pedit_header_type } pedit_header_type ;

/* Variables and functions */
 int EINVAL ; 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_ETH 133 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_IP4 132 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_IP6 131 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK 130 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_TCP 129 
#define  TCA_PEDIT_KEY_EX_HDR_TYPE_UDP 128 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 int skb_mac_offset (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_header_was_set (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int pedit_skb_hdr_offset(struct sk_buff *skb,
				enum pedit_header_type htype, int *hoffset)
{
	int ret = -EINVAL;

	switch (htype) {
	case TCA_PEDIT_KEY_EX_HDR_TYPE_ETH:
		if (skb_mac_header_was_set(skb)) {
			*hoffset = skb_mac_offset(skb);
			ret = 0;
		}
		break;
	case TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK:
	case TCA_PEDIT_KEY_EX_HDR_TYPE_IP4:
	case TCA_PEDIT_KEY_EX_HDR_TYPE_IP6:
		*hoffset = skb_network_offset(skb);
		ret = 0;
		break;
	case TCA_PEDIT_KEY_EX_HDR_TYPE_TCP:
	case TCA_PEDIT_KEY_EX_HDR_TYPE_UDP:
		if (skb_transport_header_was_set(skb)) {
			*hoffset = skb_transport_offset(skb);
			ret = 0;
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}