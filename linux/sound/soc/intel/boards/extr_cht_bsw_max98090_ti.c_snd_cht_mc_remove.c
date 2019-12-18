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
struct platform_device {int dummy; } ;
struct cht_mc_private {int quirks; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int QUIRK_PMC_PLT_CLK_0 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 struct cht_mc_private* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int snd_cht_mc_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct cht_mc_private *ctx = snd_soc_card_get_drvdata(card);

	if (ctx->quirks & QUIRK_PMC_PLT_CLK_0)
		clk_disable_unprepare(ctx->mclk);

	return 0;
}