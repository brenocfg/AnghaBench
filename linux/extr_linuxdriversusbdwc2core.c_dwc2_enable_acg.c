#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ acg_enable; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCGCCTL1 ; 
 int /*<<< orphan*/  PCGCCTL1_GATEEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dwc2_enable_acg(struct dwc2_hsotg *hsotg)
{
	if (hsotg->params.acg_enable) {
		u32 pcgcctl1 = dwc2_readl(hsotg, PCGCCTL1);

		dev_dbg(hsotg->dev, "Enabling Active Clock Gating\n");
		pcgcctl1 |= PCGCCTL1_GATEEN;
		dwc2_writel(hsotg, pcgcctl1, PCGCCTL1);
	}
}