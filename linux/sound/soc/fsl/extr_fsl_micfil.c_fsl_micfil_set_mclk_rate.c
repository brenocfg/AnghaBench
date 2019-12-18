#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fsl_micfil {int /*<<< orphan*/  mclk; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int,int) ; 

__attribute__((used)) static int fsl_micfil_set_mclk_rate(struct fsl_micfil *micfil,
				    unsigned int freq)
{
	struct device *dev = &micfil->pdev->dev;
	int ret;

	clk_disable_unprepare(micfil->mclk);

	ret = clk_set_rate(micfil->mclk, freq * 1024);
	if (ret)
		dev_warn(dev, "failed to set rate (%u): %d\n",
			 freq * 1024, ret);

	clk_prepare_enable(micfil->mclk);

	return ret;
}