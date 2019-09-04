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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* tv_dac_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  FEAT_VENC_REQUIRES_TV_DAC_CLK ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__ venc ; 

__attribute__((used)) static int venc_get_clocks(struct platform_device *pdev)
{
	struct clk *clk;

	if (dss_has_feature(FEAT_VENC_REQUIRES_TV_DAC_CLK)) {
		clk = devm_clk_get(&pdev->dev, "tv_dac_clk");
		if (IS_ERR(clk)) {
			DSSERR("can't get tv_dac_clk\n");
			return PTR_ERR(clk);
		}
	} else {
		clk = NULL;
	}

	venc.tv_dac_clk = clk;

	return 0;
}