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
struct vring_rx_desc {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int wil_rxdesc_cid (struct vring_rx_desc*) ; 
 int wil_rxdesc_security (struct vring_rx_desc*) ; 
 struct vring_rx_desc* wil_skb_rxdesc (struct sk_buff*) ; 

__attribute__((used)) static void wil_get_netif_rx_params(struct sk_buff *skb, int *cid,
				    int *security)
{
	struct vring_rx_desc *d = wil_skb_rxdesc(skb);

	*cid = wil_rxdesc_cid(d); /* always 0..7, no need to check */
	*security = wil_rxdesc_security(d);
}