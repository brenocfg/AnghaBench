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
struct sun4i_i2s {void* field_rxchansel; TYPE_1__* variant; int /*<<< orphan*/  regmap; void* field_txchansel; void* field_rxchanmap; void* field_txchanmap; void* field_fmt_mode; void* field_fmt_lrclk; void* field_fmt_bclk; void* field_fmt_sr; void* field_fmt_wss; void* field_clkdiv_mclk_en; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  field_rxchansel; int /*<<< orphan*/  field_txchansel; int /*<<< orphan*/  field_rxchanmap; int /*<<< orphan*/  field_txchanmap; int /*<<< orphan*/  field_fmt_mode; int /*<<< orphan*/  field_fmt_lrclk; int /*<<< orphan*/  field_fmt_bclk; int /*<<< orphan*/  field_fmt_sr; int /*<<< orphan*/  field_fmt_wss; int /*<<< orphan*/  field_clkdiv_mclk_en; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* devm_regmap_field_alloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_i2s_init_regmap_fields(struct device *dev,
					struct sun4i_i2s *i2s)
{
	i2s->field_clkdiv_mclk_en =
		devm_regmap_field_alloc(dev, i2s->regmap,
					i2s->variant->field_clkdiv_mclk_en);
	if (IS_ERR(i2s->field_clkdiv_mclk_en))
		return PTR_ERR(i2s->field_clkdiv_mclk_en);

	i2s->field_fmt_wss =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_wss);
	if (IS_ERR(i2s->field_fmt_wss))
		return PTR_ERR(i2s->field_fmt_wss);

	i2s->field_fmt_sr =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_sr);
	if (IS_ERR(i2s->field_fmt_sr))
		return PTR_ERR(i2s->field_fmt_sr);

	i2s->field_fmt_bclk =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_bclk);
	if (IS_ERR(i2s->field_fmt_bclk))
		return PTR_ERR(i2s->field_fmt_bclk);

	i2s->field_fmt_lrclk =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_lrclk);
	if (IS_ERR(i2s->field_fmt_lrclk))
		return PTR_ERR(i2s->field_fmt_lrclk);

	i2s->field_fmt_mode =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_fmt_mode);
	if (IS_ERR(i2s->field_fmt_mode))
		return PTR_ERR(i2s->field_fmt_mode);

	i2s->field_txchanmap =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_txchanmap);
	if (IS_ERR(i2s->field_txchanmap))
		return PTR_ERR(i2s->field_txchanmap);

	i2s->field_rxchanmap =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_rxchanmap);
	if (IS_ERR(i2s->field_rxchanmap))
		return PTR_ERR(i2s->field_rxchanmap);

	i2s->field_txchansel =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_txchansel);
	if (IS_ERR(i2s->field_txchansel))
		return PTR_ERR(i2s->field_txchansel);

	i2s->field_rxchansel =
			devm_regmap_field_alloc(dev, i2s->regmap,
						i2s->variant->field_rxchansel);
	return PTR_ERR_OR_ZERO(i2s->field_rxchansel);
}