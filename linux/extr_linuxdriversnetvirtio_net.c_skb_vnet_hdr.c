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
struct virtio_net_hdr_mrg_rxbuf {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;

/* Variables and functions */

__attribute__((used)) static inline struct virtio_net_hdr_mrg_rxbuf *skb_vnet_hdr(struct sk_buff *skb)
{
	return (struct virtio_net_hdr_mrg_rxbuf *)skb->cb;
}