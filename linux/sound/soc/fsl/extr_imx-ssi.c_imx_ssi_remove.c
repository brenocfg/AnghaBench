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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct imx_ssi {int flags; int /*<<< orphan*/  clk; int /*<<< orphan*/  fiq_init; } ;

/* Variables and functions */
 int IMX_SSI_USE_AC97 ; 
 int /*<<< orphan*/ * ac97_ssi ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_pcm_fiq_exit (struct platform_device*) ; 
 struct imx_ssi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_ssi_remove(struct platform_device *pdev)
{
	struct imx_ssi *ssi = platform_get_drvdata(pdev);

	if (!ssi->fiq_init)
		imx_pcm_fiq_exit(pdev);

	snd_soc_unregister_component(&pdev->dev);

	if (ssi->flags & IMX_SSI_USE_AC97)
		ac97_ssi = NULL;

	clk_disable_unprepare(ssi->clk);
	snd_soc_set_ac97_ops(NULL);

	return 0;
}