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
struct sun4i_i2s {void* field_fmt_sr; TYPE_1__* variant; int /*<<< orphan*/  regmap; void* field_fmt_wss; void* field_clkdiv_mclk_en; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  field_fmt_sr; int /*<<< orphan*/  field_fmt_wss; int /*<<< orphan*/  field_clkdiv_mclk_en; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
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

	return 0;
}