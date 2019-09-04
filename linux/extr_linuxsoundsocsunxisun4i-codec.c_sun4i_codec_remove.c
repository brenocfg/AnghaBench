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
struct sun4i_codec {int /*<<< orphan*/  clk_apb; scalar_t__ rst; } ;
struct snd_soc_card {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 struct sun4i_codec* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 

__attribute__((used)) static int sun4i_codec_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct sun4i_codec *scodec = snd_soc_card_get_drvdata(card);

	snd_soc_unregister_card(card);
	if (scodec->rst)
		reset_control_assert(scodec->rst);
	clk_disable_unprepare(scodec->clk_apb);

	return 0;
}