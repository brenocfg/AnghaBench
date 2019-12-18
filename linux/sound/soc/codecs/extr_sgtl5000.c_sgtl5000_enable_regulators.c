#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sgtl5000_priv {int num_supplies; TYPE_1__* supplies; } ;
struct regulator {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 struct sgtl5000_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int /*<<< orphan*/  regulator_bulk_free (int,TYPE_1__*) ; 
 int regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 struct regulator* regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regulator_put (struct regulator*) ; 
 int /*<<< orphan*/ * supply_names ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sgtl5000_enable_regulators(struct i2c_client *client)
{
	int ret;
	int i;
	int external_vddd = 0;
	struct regulator *vddd;
	struct sgtl5000_priv *sgtl5000 = i2c_get_clientdata(client);

	for (i = 0; i < ARRAY_SIZE(sgtl5000->supplies); i++)
		sgtl5000->supplies[i].supply = supply_names[i];

	vddd = regulator_get_optional(&client->dev, "VDDD");
	if (IS_ERR(vddd)) {
		/* See if it's just not registered yet */
		if (PTR_ERR(vddd) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
	} else {
		external_vddd = 1;
		regulator_put(vddd);
	}

	sgtl5000->num_supplies = ARRAY_SIZE(sgtl5000->supplies)
				 - 1 + external_vddd;
	ret = regulator_bulk_get(&client->dev, sgtl5000->num_supplies,
				 sgtl5000->supplies);
	if (ret)
		return ret;

	ret = regulator_bulk_enable(sgtl5000->num_supplies,
				    sgtl5000->supplies);
	if (!ret)
		usleep_range(10, 20);
	else
		regulator_bulk_free(sgtl5000->num_supplies,
				    sgtl5000->supplies);

	return ret;
}