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
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hsotg_disable_gsint(struct dwc2_hsotg *hsotg, u32 ints)
{
	u32 gsintmsk = dwc2_readl(hsotg, GINTMSK);
	u32 new_gsintmsk;

	new_gsintmsk = gsintmsk & ~ints;

	if (new_gsintmsk != gsintmsk)
		dwc2_writel(hsotg, new_gsintmsk, GINTMSK);
}