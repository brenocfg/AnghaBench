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
struct snd_i2c_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct snd_i2c_bus {int /*<<< orphan*/  (* private_free ) (struct snd_i2c_bus*) ;int /*<<< orphan*/  card; TYPE_1__ buses; scalar_t__ master; TYPE_1__ devices; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct snd_i2c_bus*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (TYPE_1__*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,struct snd_i2c_bus*) ; 
 struct snd_i2c_device* snd_i2c_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_i2c_device_free (struct snd_i2c_device*) ; 
 struct snd_i2c_bus* snd_i2c_slave_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_i2c_bus*) ; 

__attribute__((used)) static int snd_i2c_bus_free(struct snd_i2c_bus *bus)
{
	struct snd_i2c_bus *slave;
	struct snd_i2c_device *device;

	if (snd_BUG_ON(!bus))
		return -EINVAL;
	while (!list_empty(&bus->devices)) {
		device = snd_i2c_device(bus->devices.next);
		snd_i2c_device_free(device);
	}
	if (bus->master)
		list_del(&bus->buses);
	else {
		while (!list_empty(&bus->buses)) {
			slave = snd_i2c_slave_bus(bus->buses.next);
			snd_device_free(bus->card, slave);
		}
	}
	if (bus->private_free)
		bus->private_free(bus);
	kfree(bus);
	return 0;
}