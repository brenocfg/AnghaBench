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
struct snd_i2c_device {unsigned char addr; struct snd_i2c_bus* bus; int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;
struct snd_i2c_bus {int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_i2c_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int snd_i2c_device_create(struct snd_i2c_bus *bus, const char *name,
			  unsigned char addr, struct snd_i2c_device **rdevice)
{
	struct snd_i2c_device *device;

	*rdevice = NULL;
	if (snd_BUG_ON(!bus))
		return -EINVAL;
	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (device == NULL)
		return -ENOMEM;
	device->addr = addr;
	strlcpy(device->name, name, sizeof(device->name));
	list_add_tail(&device->list, &bus->devices);
	device->bus = bus;
	*rdevice = device;
	return 0;
}