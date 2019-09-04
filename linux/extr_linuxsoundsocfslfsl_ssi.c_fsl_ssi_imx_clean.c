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
struct platform_device {int dummy; } ;
struct fsl_ssi {int /*<<< orphan*/  clk; int /*<<< orphan*/  has_ipg_clk_name; int /*<<< orphan*/  use_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_pcm_fiq_exit (struct platform_device*) ; 

__attribute__((used)) static void fsl_ssi_imx_clean(struct platform_device *pdev, struct fsl_ssi *ssi)
{
	if (!ssi->use_dma)
		imx_pcm_fiq_exit(pdev);
	if (!ssi->has_ipg_clk_name)
		clk_disable_unprepare(ssi->clk);
}