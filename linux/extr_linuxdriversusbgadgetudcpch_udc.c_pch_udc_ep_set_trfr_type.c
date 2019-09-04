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
typedef  int u8 ;
struct pch_udc_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_EPCTL_ADDR ; 
 int UDC_EPCTL_ET_MASK ; 
 int UDC_EPCTL_ET_SHIFT ; 
 int /*<<< orphan*/  pch_udc_ep_writel (struct pch_udc_ep*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pch_udc_ep_set_trfr_type(struct pch_udc_ep *ep,
					u8 type)
{
	pch_udc_ep_writel(ep, ((type << UDC_EPCTL_ET_SHIFT) &
				UDC_EPCTL_ET_MASK), UDC_EPCTL_ADDR);
}