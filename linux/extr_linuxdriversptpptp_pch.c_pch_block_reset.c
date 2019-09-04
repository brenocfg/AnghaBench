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
struct pch_dev {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int PCH_TSC_RESET ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pch_block_reset(struct pch_dev *chip)
{
	u32 val;
	/* Reset Hardware Assist block */
	val = ioread32(&chip->regs->control) | PCH_TSC_RESET;
	iowrite32(val, (&chip->regs->control));
	val = val & ~PCH_TSC_RESET;
	iowrite32(val, (&chip->regs->control));
}