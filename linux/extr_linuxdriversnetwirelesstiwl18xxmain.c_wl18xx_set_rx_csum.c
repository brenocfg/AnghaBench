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
struct wl1271_rx_descriptor {int status; } ;
struct wl1271 {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int WL18XX_RX_CHECKSUM_MASK ; 

__attribute__((used)) static void wl18xx_set_rx_csum(struct wl1271 *wl,
			       struct wl1271_rx_descriptor *desc,
			       struct sk_buff *skb)
{
	if (desc->status & WL18XX_RX_CHECKSUM_MASK)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
}