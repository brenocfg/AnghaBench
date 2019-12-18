#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ shared_lrclk; } ;
struct wm8960_priv {int /*<<< orphan*/  regmap; TYPE_1__ pdata; int /*<<< orphan*/  mclk; } ;
struct wm8960_data {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_9__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_3__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM8960_ADDCTL2 ; 
 int /*<<< orphan*/  WM8960_LADC ; 
 int /*<<< orphan*/  WM8960_LDAC ; 
 int /*<<< orphan*/  WM8960_LINVOL ; 
 int /*<<< orphan*/  WM8960_LOUT1 ; 
 int /*<<< orphan*/  WM8960_LOUT2 ; 
 int /*<<< orphan*/  WM8960_RADC ; 
 int /*<<< orphan*/  WM8960_RDAC ; 
 int /*<<< orphan*/  WM8960_RINVOL ; 
 int /*<<< orphan*/  WM8960_ROUT1 ; 
 int /*<<< orphan*/  WM8960_ROUT2 ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct wm8960_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,char*) ; 
 struct wm8960_priv* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8960_priv*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct wm8960_data*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  soc_component_dev_wm8960 ; 
 int /*<<< orphan*/  wm8960_dai ; 
 int /*<<< orphan*/  wm8960_regmap ; 
 int wm8960_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8960_set_pdata_from_of (struct i2c_client*,TYPE_1__*) ; 

__attribute__((used)) static int wm8960_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8960_data *pdata = dev_get_platdata(&i2c->dev);
	struct wm8960_priv *wm8960;
	int ret;

	wm8960 = devm_kzalloc(&i2c->dev, sizeof(struct wm8960_priv),
			      GFP_KERNEL);
	if (wm8960 == NULL)
		return -ENOMEM;

	wm8960->mclk = devm_clk_get(&i2c->dev, "mclk");
	if (IS_ERR(wm8960->mclk)) {
		if (PTR_ERR(wm8960->mclk) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
	}

	wm8960->regmap = devm_regmap_init_i2c(i2c, &wm8960_regmap);
	if (IS_ERR(wm8960->regmap))
		return PTR_ERR(wm8960->regmap);

	if (pdata)
		memcpy(&wm8960->pdata, pdata, sizeof(struct wm8960_data));
	else if (i2c->dev.of_node)
		wm8960_set_pdata_from_of(i2c, &wm8960->pdata);

	ret = wm8960_reset(wm8960->regmap);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to issue reset\n");
		return ret;
	}

	if (wm8960->pdata.shared_lrclk) {
		ret = regmap_update_bits(wm8960->regmap, WM8960_ADDCTL2,
					 0x4, 0x4);
		if (ret != 0) {
			dev_err(&i2c->dev, "Failed to enable LRCM: %d\n",
				ret);
			return ret;
		}
	}

	/* Latch the update bits */
	regmap_update_bits(wm8960->regmap, WM8960_LINVOL, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_RINVOL, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LADC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_RADC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LDAC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_RDAC, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LOUT1, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_ROUT1, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_LOUT2, 0x100, 0x100);
	regmap_update_bits(wm8960->regmap, WM8960_ROUT2, 0x100, 0x100);

	i2c_set_clientdata(i2c, wm8960);

	ret = devm_snd_soc_register_component(&i2c->dev,
			&soc_component_dev_wm8960, &wm8960_dai, 1);

	return ret;
}