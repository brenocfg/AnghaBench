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
struct snd_soc_card {int dummy; } ;
struct mop500_ab8500_drvdata {int /*<<< orphan*/ * clk_ptr_intclk; int /*<<< orphan*/ * clk_ptr_ulpclk; int /*<<< orphan*/ * clk_ptr_sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 struct mop500_ab8500_drvdata* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct mop500_ab8500_drvdata*) ; 

void mop500_ab8500_remove(struct snd_soc_card *card)
{
	struct mop500_ab8500_drvdata *drvdata = snd_soc_card_get_drvdata(card);

	if (drvdata->clk_ptr_sysclk != NULL)
		clk_put(drvdata->clk_ptr_sysclk);
	if (drvdata->clk_ptr_ulpclk != NULL)
		clk_put(drvdata->clk_ptr_ulpclk);
	if (drvdata->clk_ptr_intclk != NULL)
		clk_put(drvdata->clk_ptr_intclk);

	snd_soc_card_set_drvdata(card, drvdata);
}