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
struct clk {int dummy; } ;
struct arizona_fll {struct arizona* arizona; } ;
struct arizona {struct clk** mclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ARIZONA_FLL1_CLK_REF_SRC_MASK ; 
 unsigned int ARIZONA_FLL1_CLK_REF_SRC_SHIFT ; 
#define  ARIZONA_FLL_SRC_MCLK1 129 
#define  ARIZONA_FLL_SRC_MCLK2 128 
 size_t ARIZONA_MCLK1 ; 
 size_t ARIZONA_MCLK2 ; 
 int /*<<< orphan*/  arizona_fll_err (struct arizona_fll*,char*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int arizona_set_fll_clks(struct arizona_fll *fll, int base, bool ena)
{
	struct arizona *arizona = fll->arizona;
	unsigned int val;
	struct clk *clk;
	int ret;

	ret = regmap_read(arizona->regmap, base + 6, &val);
	if (ret != 0) {
		arizona_fll_err(fll, "Failed to read current source: %d\n",
				ret);
		return ret;
	}

	val &= ARIZONA_FLL1_CLK_REF_SRC_MASK;
	val >>= ARIZONA_FLL1_CLK_REF_SRC_SHIFT;

	switch (val) {
	case ARIZONA_FLL_SRC_MCLK1:
		clk = arizona->mclk[ARIZONA_MCLK1];
		break;
	case ARIZONA_FLL_SRC_MCLK2:
		clk = arizona->mclk[ARIZONA_MCLK2];
		break;
	default:
		return 0;
	}

	if (ena) {
		return clk_prepare_enable(clk);
	} else {
		clk_disable_unprepare(clk);
		return 0;
	}
}