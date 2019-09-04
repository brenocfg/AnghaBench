#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct w1_slave {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; struct w1_f19_data* family_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int /*<<< orphan*/ * quirks; TYPE_1__ dev; int /*<<< orphan*/  name; struct w1_slave* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct w1_f19_data {int speed; TYPE_2__ adapter; int /*<<< orphan*/  stretch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __w1_f19_set_i2c_speed (struct w1_slave*,int) ; 
 struct w1_f19_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int i2c_speed ; 
 int /*<<< orphan*/  i2c_stretch ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  w1_f19_i2c_adapter_quirks ; 
 int /*<<< orphan*/  w1_f19_i2c_algorithm ; 

__attribute__((used)) static int w1_f19_add_slave(struct w1_slave *sl)
{
	struct w1_f19_data *data = NULL;

	/* Allocate memory for slave specific data. */
	data = devm_kzalloc(&sl->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	sl->family_data = data;

	/* Setup default I2C speed on slave. */
	switch (i2c_speed) {
	case 100:
		__w1_f19_set_i2c_speed(sl, 0);
		break;
	case 400:
		__w1_f19_set_i2c_speed(sl, 1);
		break;
	case 900:
		__w1_f19_set_i2c_speed(sl, 2);
		break;
	default:
		/*
		 * A i2c_speed module parameter of anything else
		 * than 100, 400, 900 means not to touch the
		 * speed of the DS28E17.
		 * We assume 400kBaud, the power-on value.
		 */
		data->speed = 1;
	}

	/*
	 * Setup default busy stretch
	 * configuration for the DS28E17.
	 */
	data->stretch = i2c_stretch;

	/* Setup I2C adapter. */
	data->adapter.owner      = THIS_MODULE;
	data->adapter.algo       = &w1_f19_i2c_algorithm;
	data->adapter.algo_data  = sl;
	strcpy(data->adapter.name, "w1-");
	strcat(data->adapter.name, sl->name);
	data->adapter.dev.parent = &sl->dev;
	data->adapter.quirks     = &w1_f19_i2c_adapter_quirks;

	return i2c_add_adapter(&data->adapter);
}