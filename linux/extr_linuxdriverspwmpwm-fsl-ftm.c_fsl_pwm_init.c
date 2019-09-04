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
struct fsl_pwm_chip {int /*<<< orphan*/  ipg_clk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_CNTIN ; 
 int /*<<< orphan*/  FTM_OUTINIT ; 
 int /*<<< orphan*/  FTM_OUTMASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsl_pwm_init(struct fsl_pwm_chip *fpc)
{
	int ret;

	ret = clk_prepare_enable(fpc->ipg_clk);
	if (ret)
		return ret;

	regmap_write(fpc->regmap, FTM_CNTIN, 0x00);
	regmap_write(fpc->regmap, FTM_OUTINIT, 0x00);
	regmap_write(fpc->regmap, FTM_OUTMASK, 0xFF);

	clk_disable_unprepare(fpc->ipg_clk);

	return 0;
}