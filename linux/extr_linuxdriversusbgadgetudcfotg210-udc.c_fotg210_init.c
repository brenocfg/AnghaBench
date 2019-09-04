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
struct fotg210_udc {scalar_t__ reg; } ;

/* Variables and functions */
 int DMCR_GLINT_EN ; 
 int DMISGR0_MCX_COMEND ; 
 scalar_t__ FOTG210_DMCR ; 
 scalar_t__ FOTG210_DMISGR0 ; 
 scalar_t__ FOTG210_DMISGR1 ; 
 scalar_t__ FOTG210_GMIR ; 
 int GMIR_INT_POLARITY ; 
 int GMIR_MHC_INT ; 
 int GMIR_MOTG_INT ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void fotg210_init(struct fotg210_udc *fotg210)
{
	u32 value;

	/* disable global interrupt and set int polarity to active high */
	iowrite32(GMIR_MHC_INT | GMIR_MOTG_INT | GMIR_INT_POLARITY,
		  fotg210->reg + FOTG210_GMIR);

	/* disable device global interrupt */
	value = ioread32(fotg210->reg + FOTG210_DMCR);
	value &= ~DMCR_GLINT_EN;
	iowrite32(value, fotg210->reg + FOTG210_DMCR);

	/* disable all fifo interrupt */
	iowrite32(~(u32)0, fotg210->reg + FOTG210_DMISGR1);

	/* disable cmd end */
	value = ioread32(fotg210->reg + FOTG210_DMISGR0);
	value |= DMISGR0_MCX_COMEND;
	iowrite32(value, fotg210->reg + FOTG210_DMISGR0);
}