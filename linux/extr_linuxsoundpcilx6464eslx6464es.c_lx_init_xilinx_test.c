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
typedef  scalar_t__ u32 ;
struct lx6464es {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ePLX_PCICR ; 
 int /*<<< orphan*/  eReg_CSM ; 
 scalar_t__ lx_dsp_reg_read (struct lx6464es*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_dsp_reg_write (struct lx6464es*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_plx_reg_write (struct lx6464es*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lx_init_xilinx_test(struct lx6464es *chip)
{
	u32 reg;

	dev_dbg(chip->card->dev, "->lx_init_xilinx_test\n");

	/* TEST if we have access to Xilinx/MicroBlaze */
	lx_dsp_reg_write(chip, eReg_CSM, 0);

	reg = lx_dsp_reg_read(chip, eReg_CSM);

	if (reg) {
		dev_err(chip->card->dev, "Problem: Reg_CSM %x.\n", reg);

		/* PCI9056_SPACE0_REMAP */
		lx_plx_reg_write(chip, ePLX_PCICR, 1);

		reg = lx_dsp_reg_read(chip, eReg_CSM);
		if (reg) {
			dev_err(chip->card->dev, "Error: Reg_CSM %x.\n", reg);
			return -EAGAIN; /* seems to be appropriate */
		}
	}

	dev_dbg(chip->card->dev, "Xilinx/MicroBlaze access test successful\n");

	return 0;
}