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
struct i2c_device_id {unsigned int driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct alc5632_priv {unsigned int id; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5632_VENDOR_ID1 ; 
 int /*<<< orphan*/  ALC5632_VENDOR_ID2 ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__ alc5632_dai ; 
 int /*<<< orphan*/  alc5632_regmap ; 
 int alc5632_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct alc5632_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct alc5632_priv*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  soc_component_device_alc5632 ; 

__attribute__((used)) static int alc5632_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct alc5632_priv *alc5632;
	int ret, ret1, ret2;
	unsigned int vid1, vid2;

	alc5632 = devm_kzalloc(&client->dev,
			 sizeof(struct alc5632_priv), GFP_KERNEL);
	if (alc5632 == NULL)
		return -ENOMEM;

	i2c_set_clientdata(client, alc5632);

	alc5632->regmap = devm_regmap_init_i2c(client, &alc5632_regmap);
	if (IS_ERR(alc5632->regmap)) {
		ret = PTR_ERR(alc5632->regmap);
		dev_err(&client->dev, "regmap_init() failed: %d\n", ret);
		return ret;
	}

	ret1 = regmap_read(alc5632->regmap, ALC5632_VENDOR_ID1, &vid1);
	ret2 = regmap_read(alc5632->regmap, ALC5632_VENDOR_ID2, &vid2);
	if (ret1 != 0 || ret2 != 0) {
		dev_err(&client->dev,
		"Failed to read chip ID: ret1=%d, ret2=%d\n", ret1, ret2);
		return -EIO;
	}

	vid2 >>= 8;

	if ((vid1 != 0x10EC) || (vid2 != id->driver_data)) {
		dev_err(&client->dev,
		"Device is not a ALC5632: VID1=0x%x, VID2=0x%x\n", vid1, vid2);
		return -EINVAL;
	}

	ret = alc5632_reset(alc5632->regmap);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to issue reset\n");
		return ret;
	}

	alc5632->id = vid2;
	switch (alc5632->id) {
	case 0x5c:
		alc5632_dai.name = "alc5632-hifi";
		break;
	default:
		return -EINVAL;
	}

	ret = devm_snd_soc_register_component(&client->dev,
		&soc_component_device_alc5632, &alc5632_dai, 1);

	if (ret < 0) {
		dev_err(&client->dev, "Failed to register component: %d\n", ret);
		return ret;
	}

	return ret;
}