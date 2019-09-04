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
struct regulator_init_data {int dummy; } ;
struct regulator_config {struct ad5398_chip_info* driver_data; struct regulator_init_data* init_data; int /*<<< orphan*/ * dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ad5398_current_data_format {int current_bits; int current_offset; int /*<<< orphan*/  max_uA; int /*<<< orphan*/  min_uA; } ;
struct ad5398_chip_info {int current_level; int current_offset; int current_mask; int /*<<< orphan*/  rdev; int /*<<< orphan*/  max_uA; int /*<<< orphan*/  min_uA; struct i2c_client* client; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__ ad5398_reg ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regulator_init_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct ad5398_chip_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ *,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ad5398_chip_info*) ; 

__attribute__((used)) static int ad5398_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct regulator_init_data *init_data = dev_get_platdata(&client->dev);
	struct regulator_config config = { };
	struct ad5398_chip_info *chip;
	const struct ad5398_current_data_format *df =
			(struct ad5398_current_data_format *)id->driver_data;

	if (!init_data)
		return -EINVAL;

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	config.dev = &client->dev;
	config.init_data = init_data;
	config.driver_data = chip;

	chip->client = client;

	chip->min_uA = df->min_uA;
	chip->max_uA = df->max_uA;
	chip->current_level = 1 << df->current_bits;
	chip->current_offset = df->current_offset;
	chip->current_mask = (chip->current_level - 1) << chip->current_offset;

	chip->rdev = devm_regulator_register(&client->dev, &ad5398_reg,
					     &config);
	if (IS_ERR(chip->rdev)) {
		dev_err(&client->dev, "failed to register %s %s\n",
			id->name, ad5398_reg.name);
		return PTR_ERR(chip->rdev);
	}

	i2c_set_clientdata(client, chip);
	dev_dbg(&client->dev, "%s regulator driver is registered.\n", id->name);
	return 0;
}