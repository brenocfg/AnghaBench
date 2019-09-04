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
struct snd_card {int dummy; } ;
struct platform_device {int dummy; } ;
struct atmel_ac97c {int /*<<< orphan*/  irq; int /*<<< orphan*/  regs; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMR ; 
 int /*<<< orphan*/  COMR ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct atmel_ac97c*) ; 
 struct atmel_ac97c* get_chip (struct snd_card*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct snd_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

__attribute__((used)) static int atmel_ac97c_remove(struct platform_device *pdev)
{
	struct snd_card *card = platform_get_drvdata(pdev);
	struct atmel_ac97c *chip = get_chip(card);

	ac97c_writel(chip, CAMR, 0);
	ac97c_writel(chip, COMR, 0);
	ac97c_writel(chip, MR,   0);

	clk_disable_unprepare(chip->pclk);
	clk_put(chip->pclk);
	iounmap(chip->regs);
	free_irq(chip->irq, chip);

	snd_card_free(card);

	return 0;
}