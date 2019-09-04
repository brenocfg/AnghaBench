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
typedef  int u32 ;
struct samsung_i2s_variant_regs {int /*<<< orphan*/  cdclkcon_off; int /*<<< orphan*/  rclksrc_off; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int clk_num; int /*<<< orphan*/ * clks; } ;
struct i2s_dai {int quirks; TYPE_1__ clk_data; int /*<<< orphan*/ * clk_table; int /*<<< orphan*/  lock; scalar_t__ addr; struct samsung_i2s_variant_regs* variant_regs; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  CLK_GATE_SET_TO_DISABLE ; 
 size_t CLK_I2S_CDCLK ; 
 size_t CLK_I2S_RCLK_PSR ; 
 size_t CLK_I2S_RCLK_SRC ; 
 int CLK_SET_RATE_NO_REPARENT ; 
 int CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ I2SMOD ; 
 scalar_t__ I2SPSR ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PSR_PSREN ; 
 int QUIRK_NO_MUXPSR ; 
 char* __clk_get_name (struct clk*) ; 
 struct clk* clk_get (struct device*,char const*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_register_divider (struct device*,char const*,char const*,int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_register_gate (struct device*,char const*,char const*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_register_mux (struct device*,char const*,char const**,int,int,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct i2s_dai* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  i2s_unregister_clocks (struct i2s_dai*) ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i2s_register_clock_provider(struct platform_device *pdev)
{
	const char * const i2s_clk_desc[] = { "cdclk", "rclk_src", "prescaler" };
	const char *clk_name[2] = { "i2s_opclk0", "i2s_opclk1" };
	const char *p_names[2] = { NULL };
	struct device *dev = &pdev->dev;
	struct i2s_dai *i2s = dev_get_drvdata(dev);
	const struct samsung_i2s_variant_regs *reg_info = i2s->variant_regs;
	const char *i2s_clk_name[ARRAY_SIZE(i2s_clk_desc)];
	struct clk *rclksrc;
	int ret, i;

	/* Register the clock provider only if it's expected in the DTB */
	if (!of_find_property(dev->of_node, "#clock-cells", NULL))
		return 0;

	/* Get the RCLKSRC mux clock parent clock names */
	for (i = 0; i < ARRAY_SIZE(p_names); i++) {
		rclksrc = clk_get(dev, clk_name[i]);
		if (IS_ERR(rclksrc))
			continue;
		p_names[i] = __clk_get_name(rclksrc);
		clk_put(rclksrc);
	}

	for (i = 0; i < ARRAY_SIZE(i2s_clk_desc); i++) {
		i2s_clk_name[i] = devm_kasprintf(dev, GFP_KERNEL, "%s_%s",
						dev_name(dev), i2s_clk_desc[i]);
		if (!i2s_clk_name[i])
			return -ENOMEM;
	}

	if (!(i2s->quirks & QUIRK_NO_MUXPSR)) {
		/* Activate the prescaler */
		u32 val = readl(i2s->addr + I2SPSR);
		writel(val | PSR_PSREN, i2s->addr + I2SPSR);

		i2s->clk_table[CLK_I2S_RCLK_SRC] = clk_register_mux(dev,
				i2s_clk_name[CLK_I2S_RCLK_SRC], p_names,
				ARRAY_SIZE(p_names),
				CLK_SET_RATE_NO_REPARENT | CLK_SET_RATE_PARENT,
				i2s->addr + I2SMOD, reg_info->rclksrc_off,
				1, 0, i2s->lock);

		i2s->clk_table[CLK_I2S_RCLK_PSR] = clk_register_divider(dev,
				i2s_clk_name[CLK_I2S_RCLK_PSR],
				i2s_clk_name[CLK_I2S_RCLK_SRC],
				CLK_SET_RATE_PARENT,
				i2s->addr + I2SPSR, 8, 6, 0, i2s->lock);

		p_names[0] = i2s_clk_name[CLK_I2S_RCLK_PSR];
		i2s->clk_data.clk_num = 2;
	}

	i2s->clk_table[CLK_I2S_CDCLK] = clk_register_gate(dev,
				i2s_clk_name[CLK_I2S_CDCLK], p_names[0],
				CLK_SET_RATE_PARENT,
				i2s->addr + I2SMOD, reg_info->cdclkcon_off,
				CLK_GATE_SET_TO_DISABLE, i2s->lock);

	i2s->clk_data.clk_num += 1;
	i2s->clk_data.clks = i2s->clk_table;

	ret = of_clk_add_provider(dev->of_node, of_clk_src_onecell_get,
				  &i2s->clk_data);
	if (ret < 0) {
		dev_err(dev, "failed to add clock provider: %d\n", ret);
		i2s_unregister_clocks(i2s);
	}

	return ret;
}