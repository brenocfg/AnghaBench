#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int ahbcfg; int dma_desc_enable; scalar_t__ host_dma; } ;
struct TYPE_4__ {int arch; } ;
struct dwc2_hsotg {TYPE_1__ params; int /*<<< orphan*/  dev; TYPE_2__ hw_params; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GAHBCFG ; 
 int GAHBCFG_CTRL_MASK ; 
 int GAHBCFG_DMA_EN ; 
#define  GHWCFG2_EXT_DMA_ARCH 130 
#define  GHWCFG2_INT_DMA_ARCH 129 
#define  GHWCFG2_SLAVE_ONLY_ARCH 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_gahbcfg_init(struct dwc2_hsotg *hsotg)
{
	u32 ahbcfg = dwc2_readl(hsotg, GAHBCFG);

	switch (hsotg->hw_params.arch) {
	case GHWCFG2_EXT_DMA_ARCH:
		dev_err(hsotg->dev, "External DMA Mode not supported\n");
		return -EINVAL;

	case GHWCFG2_INT_DMA_ARCH:
		dev_dbg(hsotg->dev, "Internal DMA Mode\n");
		if (hsotg->params.ahbcfg != -1) {
			ahbcfg &= GAHBCFG_CTRL_MASK;
			ahbcfg |= hsotg->params.ahbcfg &
				  ~GAHBCFG_CTRL_MASK;
		}
		break;

	case GHWCFG2_SLAVE_ONLY_ARCH:
	default:
		dev_dbg(hsotg->dev, "Slave Only Mode\n");
		break;
	}

	if (hsotg->params.host_dma)
		ahbcfg |= GAHBCFG_DMA_EN;
	else
		hsotg->params.dma_desc_enable = false;

	dwc2_writel(hsotg, ahbcfg, GAHBCFG);

	return 0;
}