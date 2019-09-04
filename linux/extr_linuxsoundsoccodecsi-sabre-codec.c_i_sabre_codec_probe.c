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
struct regmap {int dummy; } ;
struct i_sabre_codec_priv {struct regmap* regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct i_sabre_codec_priv*) ; 
 struct i_sabre_codec_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_sabre_codec_codec_driver ; 
 int /*<<< orphan*/  i_sabre_codec_dai ; 
 int snd_soc_register_component (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int i_sabre_codec_probe(struct device *dev, struct regmap *regmap)
{
	struct i_sabre_codec_priv *i_sabre_codec;
	int ret;

	i_sabre_codec = devm_kzalloc(dev, sizeof(*i_sabre_codec), GFP_KERNEL);
	if (!i_sabre_codec) {
		dev_err(dev, "devm_kzalloc");
		return (-ENOMEM);
	}

	i_sabre_codec->regmap = regmap;

	dev_set_drvdata(dev, i_sabre_codec);

	ret = snd_soc_register_component(dev,
			&i_sabre_codec_codec_driver, &i_sabre_codec_dai, 1);
	if (ret != 0) {
		dev_err(dev, "Failed to register CODEC: %d\n", ret);
		return ret;
	}

	return 0;
}