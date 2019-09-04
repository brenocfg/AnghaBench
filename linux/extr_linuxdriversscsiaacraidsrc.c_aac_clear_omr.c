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
typedef  int u32 ;
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  OMR; } ;

/* Variables and functions */
 int AAC_INT_MODE_MSIX ; 
 int INVALID_OMR ; 
 int KERNEL_PANIC ; 
 TYPE_1__ MUnit ; 
 int src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aac_clear_omr(struct aac_dev *dev)
{
	u32 omr_value = 0;

	omr_value = src_readl(dev, MUnit.OMR);

	/*
	 * Check for PCI Errors or Kernel Panic
	 */
	if ((omr_value == INVALID_OMR) || (omr_value & KERNEL_PANIC))
		omr_value = 0;

	/*
	 * Preserve MSIX Value if any
	 */
	src_writel(dev, MUnit.OMR, omr_value & AAC_INT_MODE_MSIX);
	src_readl(dev, MUnit.OMR);
}