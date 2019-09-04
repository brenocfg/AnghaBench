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
typedef  void vring_rx_desc ;
struct sk_buff {scalar_t__ cb; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vring_rx_desc *wil_skb_rxdesc(struct sk_buff *skb)
{
	return (void *)skb->cb;
}