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
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
typedef  struct ethhdr u8 ;
struct sk_buff {struct ethhdr* data; } ;
struct ath6kl_llc_snap_hdr {int /*<<< orphan*/  eth_type; } ;
typedef  int /*<<< orphan*/  eth_hdr ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ethhdr*,struct ethhdr*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

int ath6kl_wmi_dot3_2_dix(struct sk_buff *skb)
{
	struct ath6kl_llc_snap_hdr *llc_hdr;
	struct ethhdr eth_hdr;
	u8 *datap;

	if (WARN_ON(skb == NULL))
		return -EINVAL;

	datap = skb->data;

	memcpy(&eth_hdr, datap, sizeof(eth_hdr));

	llc_hdr = (struct ath6kl_llc_snap_hdr *) (datap + sizeof(eth_hdr));
	eth_hdr.h_proto = llc_hdr->eth_type;

	skb_pull(skb, sizeof(struct ath6kl_llc_snap_hdr));
	datap = skb->data;

	memcpy(datap, &eth_hdr, sizeof(eth_hdr));

	return 0;
}