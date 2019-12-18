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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct snd_card {struct snd_at73c213* private_data; } ;
struct snd_at73c213 {int* reg_image; TYPE_2__* ssc; TYPE_1__* board; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  dac_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  CR_TXDIS ; 
 size_t DAC_AUXG ; 
 size_t DAC_CTRL ; 
 size_t DAC_LLIG ; 
 size_t DAC_LLOG ; 
 size_t DAC_LMPG ; 
 size_t DAC_PRECH ; 
 size_t DAC_RLIG ; 
 size_t DAC_RLOG ; 
 size_t DAC_RMPG ; 
 size_t PA_CTRL ; 
 int PA_CTRL_APALP ; 
 int /*<<< orphan*/  SSC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct snd_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_at73c213_write_reg (struct snd_at73c213*,size_t,int) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int /*<<< orphan*/  ssc_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_at73c213_remove(struct spi_device *spi)
{
	struct snd_card *card = dev_get_drvdata(&spi->dev);
	struct snd_at73c213 *chip = card->private_data;
	int retval;

	/* Stop playback. */
	clk_enable(chip->ssc->clk);
	ssc_writel(chip->ssc->regs, CR, SSC_BIT(CR_TXDIS));
	clk_disable(chip->ssc->clk);

	/* Mute sound. */
	retval = snd_at73c213_write_reg(chip, DAC_LMPG, 0x3f);
	if (retval)
		goto out;
	retval = snd_at73c213_write_reg(chip, DAC_RMPG, 0x3f);
	if (retval)
		goto out;
	retval = snd_at73c213_write_reg(chip, DAC_LLOG, 0x3f);
	if (retval)
		goto out;
	retval = snd_at73c213_write_reg(chip, DAC_RLOG, 0x3f);
	if (retval)
		goto out;
	retval = snd_at73c213_write_reg(chip, DAC_LLIG, 0x11);
	if (retval)
		goto out;
	retval = snd_at73c213_write_reg(chip, DAC_RLIG, 0x11);
	if (retval)
		goto out;
	retval = snd_at73c213_write_reg(chip, DAC_AUXG, 0x11);
	if (retval)
		goto out;

	/* Turn off PA. */
	retval = snd_at73c213_write_reg(chip, PA_CTRL,
					chip->reg_image[PA_CTRL] | 0x0f);
	if (retval)
		goto out;
	msleep(10);
	retval = snd_at73c213_write_reg(chip, PA_CTRL,
					(1 << PA_CTRL_APALP) | 0x0f);
	if (retval)
		goto out;

	/* Turn off external DAC. */
	retval = snd_at73c213_write_reg(chip, DAC_CTRL, 0x0c);
	if (retval)
		goto out;
	msleep(2);
	retval = snd_at73c213_write_reg(chip, DAC_CTRL, 0x00);
	if (retval)
		goto out;

	/* Turn off master power. */
	retval = snd_at73c213_write_reg(chip, DAC_PRECH, 0x00);
	if (retval)
		goto out;

out:
	/* Stop DAC master clock. */
	clk_disable(chip->board->dac_clk);

	ssc_free(chip->ssc);
	snd_card_free(card);

	return 0;
}