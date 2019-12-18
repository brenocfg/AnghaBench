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
struct lx6464es {int freq_ratio; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CONFES_READ_PART_MASK ; 
 int ETIMEDOUT ; 
 int FREQ_RATIO_OFFSET ; 
 int FREQ_RATIO_SINGLE_MODE ; 
 int IOCR_INPUTS_OFFSET ; 
 int IOCR_OUTPUTS_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  eReg_CONFES ; 
 int /*<<< orphan*/  eReg_CSES ; 
 int lx_dsp_reg_read (struct lx6464es*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_dsp_reg_write (struct lx6464es*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lx_init_ethersound_config(struct lx6464es *chip)
{
	int i;
	u32 orig_conf_es = lx_dsp_reg_read(chip, eReg_CONFES);

	/* configure 64 io channels */
	u32 conf_es = (orig_conf_es & CONFES_READ_PART_MASK) |
		(64 << IOCR_INPUTS_OFFSET) |
		(64 << IOCR_OUTPUTS_OFFSET) |
		(FREQ_RATIO_SINGLE_MODE << FREQ_RATIO_OFFSET);

	dev_dbg(chip->card->dev, "->lx_init_ethersound\n");

	chip->freq_ratio = FREQ_RATIO_SINGLE_MODE;

	/*
	 * write it to the card !
	 * this actually kicks the ES xilinx, the first time since poweron.
	 * the MAC address in the Reg_ADMACESMSB Reg_ADMACESLSB registers
	 * is not ready before this is done, and the bit 2 in Reg_CSES is set.
	 * */
	lx_dsp_reg_write(chip, eReg_CONFES, conf_es);

	for (i = 0; i != 1000; ++i) {
		if (lx_dsp_reg_read(chip, eReg_CSES) & 4) {
			dev_dbg(chip->card->dev, "ethersound initialized after %dms\n",
				   i);
			goto ethersound_initialized;
		}
		msleep(1);
	}
	dev_warn(chip->card->dev,
		   "ethersound could not be initialized after %dms\n", i);
	return -ETIMEDOUT;

 ethersound_initialized:
	dev_dbg(chip->card->dev, "ethersound initialized\n");
	return 0;
}