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
struct sun4i_spdif_dev {int /*<<< orphan*/  spdif_clk; int /*<<< orphan*/  apb_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct sun4i_spdif_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int sun4i_spdif_runtime_resume(struct device *dev)
{
	struct sun4i_spdif_dev *host  = dev_get_drvdata(dev);
	int ret;

	ret = clk_prepare_enable(host->spdif_clk);
	if (ret)
		return ret;
	ret = clk_prepare_enable(host->apb_clk);
	if (ret)
		clk_disable_unprepare(host->spdif_clk);

	return ret;
}