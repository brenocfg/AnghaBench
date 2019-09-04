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
 int /*<<< orphan*/  UDC_DESPTR_ADDR ; 
 int /*<<< orphan*/  pch_udc_ep_writel (struct pch_udc_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pch_udc_ep_set_ddptr(struct pch_udc_ep *ep, u32 addr)
{
	pch_udc_ep_writel(ep, addr, UDC_DESPTR_ADDR);
}