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
struct stm32_sai_sub_data {int /*<<< orphan*/  sai_mclk; TYPE_1__* pdev; int /*<<< orphan*/  sai_ck; } ;
struct clk_hw {int /*<<< orphan*/  clk; int /*<<< orphan*/  init; } ;
struct stm32_sai_mclk_data {struct clk_hw hw; struct stm32_sai_sub_data* sai_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_HW_INIT (char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SAI_MCLK_NAME_LEN ; 
 scalar_t__ STM_SAI_IS_SUB_A (struct stm32_sai_sub_data*) ; 
 char* __clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_clk_hw_register (struct device*,struct clk_hw*) ; 
 char* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct stm32_sai_mclk_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,struct clk_hw*) ; 
 int /*<<< orphan*/  mclk_ops ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int stm32_sai_add_mclk_provider(struct stm32_sai_sub_data *sai)
{
	struct clk_hw *hw;
	struct stm32_sai_mclk_data *mclk;
	struct device *dev = &sai->pdev->dev;
	const char *pname = __clk_get_name(sai->sai_ck);
	char *mclk_name, *p, *s = (char *)pname;
	int ret, i = 0;

	mclk = devm_kzalloc(dev, sizeof(*mclk), GFP_KERNEL);
	if (!mclk)
		return -ENOMEM;

	mclk_name = devm_kcalloc(dev, sizeof(char),
				 SAI_MCLK_NAME_LEN, GFP_KERNEL);
	if (!mclk_name)
		return -ENOMEM;

	/*
	 * Forge mclk clock name from parent clock name and suffix.
	 * String after "_" char is stripped in parent name.
	 */
	p = mclk_name;
	while (*s && *s != '_' && (i < (SAI_MCLK_NAME_LEN - 7))) {
		*p++ = *s++;
		i++;
	}
	STM_SAI_IS_SUB_A(sai) ? strcat(p, "a_mclk") : strcat(p, "b_mclk");

	mclk->hw.init = CLK_HW_INIT(mclk_name, pname, &mclk_ops, 0);
	mclk->sai_data = sai;
	hw = &mclk->hw;

	dev_dbg(dev, "Register master clock %s\n", mclk_name);
	ret = devm_clk_hw_register(&sai->pdev->dev, hw);
	if (ret) {
		dev_err(dev, "mclk register returned %d\n", ret);
		return ret;
	}
	sai->sai_mclk = hw->clk;

	/* register mclk provider */
	return devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
}