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
struct fjes_hw {int dummy; } ;
typedef  enum REG_ICTL_MASK { ____Placeholder_REG_ICTL_MASK } REG_ICTL_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  XSCT_IMC ; 
 int /*<<< orphan*/  XSCT_IMS ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

void fjes_hw_set_irqmask(struct fjes_hw *hw,
			 enum REG_ICTL_MASK intr_mask, bool mask)
{
	if (mask)
		wr32(XSCT_IMS, intr_mask);
	else
		wr32(XSCT_IMC, intr_mask);
}