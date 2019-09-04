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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct rx_desc {int desc_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DescTag ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhine_get_vlan_tci (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void rhine_rx_vlan_tag(struct sk_buff *skb, struct rx_desc *desc,
				     int data_size)
{
	dma_rmb();
	if (unlikely(desc->desc_length & cpu_to_le32(DescTag))) {
		u16 vlan_tci;

		vlan_tci = rhine_get_vlan_tci(skb, data_size);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tci);
	}
}