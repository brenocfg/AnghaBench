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
struct pxa_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCR ; 
 int UDCCR_MASK_BITS ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_writel (struct pxa_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void udc_clear_mask_UDCCR(struct pxa_udc *udc, int mask)
{
	u32 udccr = udc_readl(udc, UDCCR);
	udc_writel(udc, UDCCR,
			(udccr & UDCCR_MASK_BITS) & ~(mask & UDCCR_MASK_BITS));
}