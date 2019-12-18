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
struct spdif_dev_data {int /*<<< orphan*/  axi_clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spdif_dev_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xlnx_spdif_remove(struct platform_device *pdev)
{
	struct spdif_dev_data *ctx = dev_get_drvdata(&pdev->dev);

	clk_disable_unprepare(ctx->axi_clk);
	return 0;
}