#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct samsung_i2s_variant_regs {int /*<<< orphan*/  cdclkcon_off; int /*<<< orphan*/  rclksrc_off; } ;
struct TYPE_4__ {int clk_num; int /*<<< orphan*/ * clks; } ;
struct samsung_i2s_priv {int quirks; TYPE_2__ clk_data; int /*<<< orphan*/ * clk_table; int /*<<< orphan*/  lock; scalar_t__ addr; struct samsung_i2s_variant_regs* variant_regs; TYPE_1__* pdev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

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
 int /*<<< orphan*/  clk_register_divider (struct device*,char const*,char const*,int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_register_gate (struct device*,char const*,char const*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_register_mux (struct device*,char const*,char const**,int,int,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  i2s_unregister_clocks (struct samsung_i2s_priv*) ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i2s_register_clock_provider(struct samsung_i2s_priv *priv)
{

	const char * const i2s_clk_desc[] = { "cdclk", "rclk_src", "prescaler" };
	const char *clk_name[2] = { "i2s_opclk0", "i2s_opclk1" };
	const char *p_names[2] = { NULL };
	struct device *dev = &priv->pdev->dev;
	const struct samsung_i2s_variant_regs *reg_info = priv->variant_regs;
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

	if (!(priv->quirks & QUIRK_NO_MUXPSR)) {
		/* Activate the prescaler */
		u32 val = readl(priv->addr + I2SPSR);
		writel(val | PSR_PSREN, priv->addr + I2SPSR);

		priv->clk_table[CLK_I2S_RCLK_SRC] = clk_register_mux(dev,
				i2s_clk_name[CLK_I2S_RCLK_SRC], p_names,
				ARRAY_SIZE(p_names),
				CLK_SET_RATE_NO_REPARENT | CLK_SET_RATE_PARENT,
				priv->addr + I2SMOD, reg_info->rclksrc_off,
				1, 0, &priv->lock);

		priv->clk_table[CLK_I2S_RCLK_PSR] = clk_register_divider(dev,
				i2s_clk_name[CLK_I2S_RCLK_PSR],
				i2s_clk_name[CLK_I2S_RCLK_SRC],
				CLK_SET_RATE_PARENT,
				priv->addr + I2SPSR, 8, 6, 0, &priv->lock);

		p_names[0] = i2s_clk_name[CLK_I2S_RCLK_PSR];
		priv->clk_data.clk_num = 2;
	}

	priv->clk_table[CLK_I2S_CDCLK] = clk_register_gate(dev,
				i2s_clk_name[CLK_I2S_CDCLK], p_names[0],
				CLK_SET_RATE_PARENT,
				priv->addr + I2SMOD, reg_info->cdclkcon_off,
				CLK_GATE_SET_TO_DISABLE, &priv->lock);

	priv->clk_data.clk_num += 1;
	priv->clk_data.clks = priv->clk_table;

	ret = of_clk_add_provider(dev->of_node, of_clk_src_onecell_get,
				  &priv->clk_data);
	if (ret < 0) {
		dev_err(dev, "failed to add clock provider: %d\n", ret);
		i2s_unregister_clocks(priv);
	}

	return ret;
}