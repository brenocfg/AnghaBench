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
typedef  int u_int32_t ;
struct aac_dev {int OIMR; int /*<<< orphan*/  msi_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  OIMR; int /*<<< orphan*/  IOAR; int /*<<< orphan*/  IDR; } ;

/* Variables and functions */
#define  AAC_CLEAR_AIF_BIT 134 
#define  AAC_CLEAR_SYNC_BIT 133 
#define  AAC_DISABLE_INTERRUPT 132 
#define  AAC_DISABLE_MSIX 131 
#define  AAC_ENABLE_INTERRUPT 130 
#define  AAC_ENABLE_INTX 129 
#define  AAC_ENABLE_MSIX 128 
 int AAC_INT_DISABLE_ALL ; 
 int AAC_INT_ENABLE_TYPE1_INTX ; 
 int AAC_INT_ENABLE_TYPE1_MSIX ; 
 TYPE_1__ MUnit ; 
 int PMC_ALL_INTERRUPT_BITS ; 
 int PMC_GLOBAL_INT_BIT0 ; 
 int PMC_GLOBAL_INT_BIT2 ; 
 int src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 

void aac_src_access_devreg(struct aac_dev *dev, int mode)
{
	u_int32_t val;

	switch (mode) {
	case AAC_ENABLE_INTERRUPT:
		src_writel(dev,
			   MUnit.OIMR,
			   dev->OIMR = (dev->msi_enabled ?
					AAC_INT_ENABLE_TYPE1_MSIX :
					AAC_INT_ENABLE_TYPE1_INTX));
		break;

	case AAC_DISABLE_INTERRUPT:
		src_writel(dev,
			   MUnit.OIMR,
			   dev->OIMR = AAC_INT_DISABLE_ALL);
		break;

	case AAC_ENABLE_MSIX:
		/* set bit 6 */
		val = src_readl(dev, MUnit.IDR);
		val |= 0x40;
		src_writel(dev,  MUnit.IDR, val);
		src_readl(dev, MUnit.IDR);
		/* unmask int. */
		val = PMC_ALL_INTERRUPT_BITS;
		src_writel(dev, MUnit.IOAR, val);
		val = src_readl(dev, MUnit.OIMR);
		src_writel(dev,
			   MUnit.OIMR,
			   val & (~(PMC_GLOBAL_INT_BIT2 | PMC_GLOBAL_INT_BIT0)));
		break;

	case AAC_DISABLE_MSIX:
		/* reset bit 6 */
		val = src_readl(dev, MUnit.IDR);
		val &= ~0x40;
		src_writel(dev, MUnit.IDR, val);
		src_readl(dev, MUnit.IDR);
		break;

	case AAC_CLEAR_AIF_BIT:
		/* set bit 5 */
		val = src_readl(dev, MUnit.IDR);
		val |= 0x20;
		src_writel(dev, MUnit.IDR, val);
		src_readl(dev, MUnit.IDR);
		break;

	case AAC_CLEAR_SYNC_BIT:
		/* set bit 4 */
		val = src_readl(dev, MUnit.IDR);
		val |= 0x10;
		src_writel(dev, MUnit.IDR, val);
		src_readl(dev, MUnit.IDR);
		break;

	case AAC_ENABLE_INTX:
		/* set bit 7 */
		val = src_readl(dev, MUnit.IDR);
		val |= 0x80;
		src_writel(dev, MUnit.IDR, val);
		src_readl(dev, MUnit.IDR);
		/* unmask int. */
		val = PMC_ALL_INTERRUPT_BITS;
		src_writel(dev, MUnit.IOAR, val);
		src_readl(dev, MUnit.IOAR);
		val = src_readl(dev, MUnit.OIMR);
		src_writel(dev, MUnit.OIMR,
				val & (~(PMC_GLOBAL_INT_BIT2)));
		break;

	default:
		break;
	}
}