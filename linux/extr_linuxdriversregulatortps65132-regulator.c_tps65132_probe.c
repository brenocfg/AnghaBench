#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tps65132_regulator {TYPE_1__** rdesc; int /*<<< orphan*/ * rdev; int /*<<< orphan*/  rmap; struct device* dev; } ;
struct regulator_config {struct tps65132_regulator* driver_data; struct device* dev; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TPS65132_MAX_REGULATORS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct tps65132_regulator* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_register (struct device*,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps65132_regulator*) ; 
 int /*<<< orphan*/  tps65132_regmap_config ; 
 TYPE_1__* tps_regs_desc ; 

__attribute__((used)) static int tps65132_probe(struct i2c_client *client,
			  const struct i2c_device_id *client_id)
{
	struct device *dev = &client->dev;
	struct tps65132_regulator *tps;
	struct regulator_config config = { };
	int id;
	int ret;

	tps = devm_kzalloc(dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	tps->rmap = devm_regmap_init_i2c(client, &tps65132_regmap_config);
	if (IS_ERR(tps->rmap)) {
		ret = PTR_ERR(tps->rmap);
		dev_err(dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(client, tps);
	tps->dev = dev;

	for (id = 0; id < TPS65132_MAX_REGULATORS; ++id) {
		tps->rdesc[id] = &tps_regs_desc[id];

		config.regmap = tps->rmap;
		config.dev = dev;
		config.driver_data = tps;

		tps->rdev[id] = devm_regulator_register(dev,
					tps->rdesc[id], &config);
		if (IS_ERR(tps->rdev[id])) {
			ret = PTR_ERR(tps->rdev[id]);
			dev_err(dev, "regulator %s register failed: %d\n",
				tps->rdesc[id]->name, ret);
			return ret;
		}
	}
	return 0;
}