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
struct snd_at73c213 {TYPE_2__* board; TYPE_1__* ssc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dac_clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_TXEN ; 
 int /*<<< orphan*/  DAC_AUXG ; 
 int /*<<< orphan*/  DAC_CTRL ; 
 int DAC_CTRL_ONDACL ; 
 int DAC_CTRL_ONDACR ; 
 int DAC_CTRL_ONLNOL ; 
 int DAC_CTRL_ONLNOR ; 
 int /*<<< orphan*/  DAC_LLIG ; 
 int /*<<< orphan*/  DAC_LLOG ; 
 int /*<<< orphan*/  DAC_LMPG ; 
 int /*<<< orphan*/  DAC_PRECH ; 
 int DAC_PRECH_ONMSTR ; 
 int /*<<< orphan*/  DAC_RLIG ; 
 int /*<<< orphan*/  DAC_RLOG ; 
 int /*<<< orphan*/  DAC_RMPG ; 
 int /*<<< orphan*/  DAC_RST ; 
 int /*<<< orphan*/  PA_CTRL ; 
 int PA_CTRL_APALP ; 
 int PA_CTRL_APAPRECH ; 
 int /*<<< orphan*/  SSC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_at73c213_set_bitrate (struct snd_at73c213*) ; 
 int snd_at73c213_write_reg (struct snd_at73c213*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_at73c213_chip_init(struct snd_at73c213 *chip)
{
	int retval;
	unsigned char dac_ctrl = 0;

	retval = snd_at73c213_set_bitrate(chip);
	if (retval)
		goto out;

	/* Enable DAC master clock. */
	clk_enable(chip->board->dac_clk);

	/* Initialize at73c213 on SPI bus. */
	retval = snd_at73c213_write_reg(chip, DAC_RST, 0x04);
	if (retval)
		goto out_clk;
	msleep(1);
	retval = snd_at73c213_write_reg(chip, DAC_RST, 0x03);
	if (retval)
		goto out_clk;

	/* Precharge everything. */
	retval = snd_at73c213_write_reg(chip, DAC_PRECH, 0xff);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, PA_CTRL, (1<<PA_CTRL_APAPRECH));
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_CTRL,
			(1<<DAC_CTRL_ONLNOL) | (1<<DAC_CTRL_ONLNOR));
	if (retval)
		goto out_clk;

	msleep(50);

	/* Stop precharging PA. */
	retval = snd_at73c213_write_reg(chip, PA_CTRL,
			(1<<PA_CTRL_APALP) | 0x0f);
	if (retval)
		goto out_clk;

	msleep(450);

	/* Stop precharging DAC, turn on master power. */
	retval = snd_at73c213_write_reg(chip, DAC_PRECH, (1<<DAC_PRECH_ONMSTR));
	if (retval)
		goto out_clk;

	msleep(1);

	/* Turn on DAC. */
	dac_ctrl = (1<<DAC_CTRL_ONDACL) | (1<<DAC_CTRL_ONDACR)
		| (1<<DAC_CTRL_ONLNOL) | (1<<DAC_CTRL_ONLNOR);

	retval = snd_at73c213_write_reg(chip, DAC_CTRL, dac_ctrl);
	if (retval)
		goto out_clk;

	/* Mute sound. */
	retval = snd_at73c213_write_reg(chip, DAC_LMPG, 0x3f);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_RMPG, 0x3f);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_LLOG, 0x3f);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_RLOG, 0x3f);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_LLIG, 0x11);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_RLIG, 0x11);
	if (retval)
		goto out_clk;
	retval = snd_at73c213_write_reg(chip, DAC_AUXG, 0x11);
	if (retval)
		goto out_clk;

	/* Enable I2S device, i.e. clock output. */
	ssc_writel(chip->ssc->regs, CR, SSC_BIT(CR_TXEN));

	goto out;

out_clk:
	clk_disable(chip->board->dac_clk);
out:
	return retval;
}