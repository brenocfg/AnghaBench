#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pt2258 {int /*<<< orphan*/  i2c_dev; TYPE_2__* i2c_bus; int /*<<< orphan*/  card; } ;
struct snd_ice1712 {TYPE_2__* i2c; int /*<<< orphan*/  card; struct revo51_spec* spec; } ;
struct revo51_spec {struct snd_pt2258* pt2258; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bit; } ;
struct TYPE_5__ {TYPE_1__ hw_ops; struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct revo51_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revo51_bit_ops ; 
 int snd_i2c_bus_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int snd_i2c_device_create (TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pt2258_reset (struct snd_pt2258*) ; 

__attribute__((used)) static int revo51_i2c_init(struct snd_ice1712 *ice,
			   struct snd_pt2258 *pt)
{
	struct revo51_spec *spec;
	int err;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;

	/* create the I2C bus */
	err = snd_i2c_bus_create(ice->card, "ICE1724 GPIO6", NULL, &ice->i2c);
	if (err < 0)
		return err;

	ice->i2c->private_data = ice;
	ice->i2c->hw_ops.bit = &revo51_bit_ops;

	/* create the I2C device */
	err = snd_i2c_device_create(ice->i2c, "PT2258", 0x40, &spec->dev);
	if (err < 0)
		return err;

	pt->card = ice->card;
	pt->i2c_bus = ice->i2c;
	pt->i2c_dev = spec->dev;
	spec->pt2258 = pt;

	snd_pt2258_reset(pt);

	return 0;
}