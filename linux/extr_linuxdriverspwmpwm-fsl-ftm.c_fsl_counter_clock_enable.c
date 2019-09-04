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
struct fsl_pwm_chip {size_t cnt_select; int /*<<< orphan*/ * clk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 size_t FSL_PWM_CLK_CNTEN ; 
 int /*<<< orphan*/  FTM_SC ; 
 int /*<<< orphan*/  FTM_SC_CLK (size_t) ; 
 int /*<<< orphan*/  FTM_SC_CLK_MASK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_counter_clock_enable(struct fsl_pwm_chip *fpc)
{
	int ret;

	/* select counter clock source */
	regmap_update_bits(fpc->regmap, FTM_SC, FTM_SC_CLK_MASK,
			   FTM_SC_CLK(fpc->cnt_select));

	ret = clk_prepare_enable(fpc->clk[fpc->cnt_select]);
	if (ret)
		return ret;

	ret = clk_prepare_enable(fpc->clk[FSL_PWM_CLK_CNTEN]);
	if (ret) {
		clk_disable_unprepare(fpc->clk[fpc->cnt_select]);
		return ret;
	}

	return 0;
}