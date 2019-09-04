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
typedef  int /*<<< orphan*/  u32 ;
struct pch_udc_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_EPSTS_ADDR ; 
 int /*<<< orphan*/  pch_udc_ep_readl (struct pch_udc_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 pch_udc_read_ep_status(struct pch_udc_ep *ep)
{
	return pch_udc_ep_readl(ep, UDC_EPSTS_ADDR);
}