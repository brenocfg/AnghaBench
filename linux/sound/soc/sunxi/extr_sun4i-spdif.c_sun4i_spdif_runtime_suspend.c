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
struct sun4i_spdif_dev {int /*<<< orphan*/  apb_clk; int /*<<< orphan*/  spdif_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_spdif_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int sun4i_spdif_runtime_suspend(struct device *dev)
{
	struct sun4i_spdif_dev *host  = dev_get_drvdata(dev);

	clk_disable_unprepare(host->spdif_clk);
	clk_disable_unprepare(host->apb_clk);

	return 0;
}