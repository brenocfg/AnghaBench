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
struct pxa25x_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCR ; 
 int UDCCR_MASK_BITS ; 
 int udc_get_reg (struct pxa25x_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_set_reg (struct pxa25x_udc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void udc_ack_int_UDCCR(struct pxa25x_udc *dev, int mask)
{
	/* udccr contains the bits we dont want to change */
	u32 udccr = udc_get_reg(dev, UDCCR) & UDCCR_MASK_BITS;

	udc_set_reg(dev, udccr | (mask & ~UDCCR_MASK_BITS), UDCCR);
}