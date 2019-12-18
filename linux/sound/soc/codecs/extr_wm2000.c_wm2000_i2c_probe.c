#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct wm2000_priv {int speech_clarity; int anc_download_size; int* anc_download; int anc_eng_ena; int anc_active; int spk_ena; TYPE_1__* supplies; struct i2c_client* i2c; int /*<<< orphan*/  mclk; int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; } ;
struct wm2000_platform_data {char* download_file; int /*<<< orphan*/  speech_enh_disable; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int WM2000_NUM_SUPPLIES ; 
 int /*<<< orphan*/  WM2000_REG_ID1 ; 
 int /*<<< orphan*/  WM2000_REG_ID2 ; 
 int /*<<< orphan*/  WM2000_REG_REVISON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct wm2000_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct wm2000_priv*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_component_dev_wm2000 ; 
 int /*<<< orphan*/  wm2000_regmap ; 
 int /*<<< orphan*/  wm2000_reset (struct wm2000_priv*) ; 
 int /*<<< orphan*/ * wm2000_supplies ; 

__attribute__((used)) static int wm2000_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *i2c_id)
{
	struct wm2000_priv *wm2000;
	struct wm2000_platform_data *pdata;
	const char *filename;
	const struct firmware *fw = NULL;
	int ret, i;
	unsigned int reg;
	u16 id;

	wm2000 = devm_kzalloc(&i2c->dev, sizeof(*wm2000), GFP_KERNEL);
	if (!wm2000)
		return -ENOMEM;

	mutex_init(&wm2000->lock);

	dev_set_drvdata(&i2c->dev, wm2000);

	wm2000->regmap = devm_regmap_init_i2c(i2c, &wm2000_regmap);
	if (IS_ERR(wm2000->regmap)) {
		ret = PTR_ERR(wm2000->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		goto out;
	}

	for (i = 0; i < WM2000_NUM_SUPPLIES; i++)
		wm2000->supplies[i].supply = wm2000_supplies[i];

	ret = devm_regulator_bulk_get(&i2c->dev, WM2000_NUM_SUPPLIES,
				      wm2000->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to get supplies: %d\n", ret);
		return ret;
	}

	ret = regulator_bulk_enable(WM2000_NUM_SUPPLIES, wm2000->supplies);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		return ret;
	}

	/* Verify that this is a WM2000 */
	ret = regmap_read(wm2000->regmap, WM2000_REG_ID1, &reg);
	if (ret != 0) {
		dev_err(&i2c->dev, "Unable to read ID1: %d\n", ret);
		return ret;
	}
	id = reg << 8;
	ret = regmap_read(wm2000->regmap, WM2000_REG_ID2, &reg);
	if (ret != 0) {
		dev_err(&i2c->dev, "Unable to read ID2: %d\n", ret);
		return ret;
	}
	id |= reg & 0xff;

	if (id != 0x2000) {
		dev_err(&i2c->dev, "Device is not a WM2000 - ID %x\n", id);
		ret = -ENODEV;
		goto err_supplies;
	}

	ret = regmap_read(wm2000->regmap, WM2000_REG_REVISON, &reg);
	if (ret != 0) {
		dev_err(&i2c->dev, "Unable to read Revision: %d\n", ret);
		return ret;
	}
	dev_info(&i2c->dev, "revision %c\n", reg + 'A');

	wm2000->mclk = devm_clk_get(&i2c->dev, "MCLK");
	if (IS_ERR(wm2000->mclk)) {
		ret = PTR_ERR(wm2000->mclk);
		dev_err(&i2c->dev, "Failed to get MCLK: %d\n", ret);
		goto err_supplies;
	}

	filename = "wm2000_anc.bin";
	pdata = dev_get_platdata(&i2c->dev);
	if (pdata) {
		wm2000->speech_clarity = !pdata->speech_enh_disable;

		if (pdata->download_file)
			filename = pdata->download_file;
	}

	ret = request_firmware(&fw, filename, &i2c->dev);
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to acquire ANC data: %d\n", ret);
		goto err_supplies;
	}

	/* Pre-cook the concatenation of the register address onto the image */
	wm2000->anc_download_size = fw->size + 2;
	wm2000->anc_download = devm_kzalloc(&i2c->dev,
					    wm2000->anc_download_size,
					    GFP_KERNEL);
	if (wm2000->anc_download == NULL) {
		ret = -ENOMEM;
		goto err_supplies;
	}

	wm2000->anc_download[0] = 0x80;
	wm2000->anc_download[1] = 0x00;
	memcpy(wm2000->anc_download + 2, fw->data, fw->size);

	wm2000->anc_eng_ena = 1;
	wm2000->anc_active = 1;
	wm2000->spk_ena = 1;
	wm2000->i2c = i2c;

	wm2000_reset(wm2000);

	ret = devm_snd_soc_register_component(&i2c->dev,
					&soc_component_dev_wm2000, NULL, 0);

err_supplies:
	regulator_bulk_disable(WM2000_NUM_SUPPLIES, wm2000->supplies);

out:
	release_firmware(fw);
	return ret;
}