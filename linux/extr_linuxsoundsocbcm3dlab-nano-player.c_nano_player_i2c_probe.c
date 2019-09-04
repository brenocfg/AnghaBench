#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {struct device_node* cpu_of_node; int /*<<< orphan*/ * cpu_dai_name; struct device_node* platform_of_node; int /*<<< orphan*/ * platform_name; } ;
struct regmap {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_card (TYPE_3__*,TYPE_1__*) ; 
 TYPE_1__ nano_player_card ; 
 struct snd_soc_dai_link nano_player_link ; 
 int /*<<< orphan*/  nano_player_regmap ; 
 struct device_node* of_parse_phandle (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct regmap*) ; 

__attribute__((used)) static int nano_player_i2c_probe(struct i2c_client *i2c,
				 const struct i2c_device_id *id)
{
	struct regmap *regmap;
	int ret;

	regmap = devm_regmap_init_i2c(i2c, &nano_player_regmap);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to init regmap %d\n", ret);
		return ret;
	}

	if (i2c->dev.of_node) {
		struct snd_soc_dai_link *dai = &nano_player_link;
		struct device_node *node;

		/* cpu handle configured by device tree */
		node = of_parse_phandle(i2c->dev.of_node, "i2s-controller", 0);
		if (node) {
			dai->platform_name = NULL;
			dai->platform_of_node = node;
			dai->cpu_dai_name = NULL;
			dai->cpu_of_node = node;
		}
	}

	nano_player_card.dev = &i2c->dev;
	snd_soc_card_set_drvdata(&nano_player_card, regmap);
	ret = devm_snd_soc_register_card(&i2c->dev, &nano_player_card);

	if (ret && ret != -EPROBE_DEFER)
		dev_err(&i2c->dev, "Failed to register card %d\n", ret);

	return ret;
}