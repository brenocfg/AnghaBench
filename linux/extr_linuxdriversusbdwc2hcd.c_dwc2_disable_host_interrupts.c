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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GINTMSK ; 
 int GINTSTS_DISCONNINT ; 
 int GINTSTS_HCHINT ; 
 int GINTSTS_NPTXFEMP ; 
 int GINTSTS_PRTINT ; 
 int GINTSTS_PTXFEMP ; 
 int GINTSTS_SOF ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_disable_host_interrupts(struct dwc2_hsotg *hsotg)
{
	u32 intmsk = dwc2_readl(hsotg, GINTMSK);

	/* Disable host mode interrupts without disturbing common interrupts */
	intmsk &= ~(GINTSTS_SOF | GINTSTS_PRTINT | GINTSTS_HCHINT |
		    GINTSTS_PTXFEMP | GINTSTS_NPTXFEMP | GINTSTS_DISCONNINT);
	dwc2_writel(hsotg, intmsk, GINTMSK);
}