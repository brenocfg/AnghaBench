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
typedef  int u32 ;
struct pch_udc_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_BUFOUT_MAXPKT_ADDR ; 
 int pch_udc_ep_readl (struct pch_udc_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_udc_ep_writel (struct pch_udc_ep*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_udc_ep_set_maxpkt(struct pch_udc_ep *ep, u32 pkt_size)
{
	u32 data = pch_udc_ep_readl(ep, UDC_BUFOUT_MAXPKT_ADDR);
	data = (data & 0xffff0000) | (pkt_size & 0xffff);
	pch_udc_ep_writel(ep, data, UDC_BUFOUT_MAXPKT_ADDR);
}