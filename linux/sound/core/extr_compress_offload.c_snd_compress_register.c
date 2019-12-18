#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_compr {int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {int /*<<< orphan*/  trigger; int /*<<< orphan*/  set_params; int /*<<< orphan*/  free; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_mutex ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_compress_add_device (struct snd_compr*) ; 

int snd_compress_register(struct snd_compr *device)
{
	int retval;

	if (device->name == NULL || device->ops == NULL)
		return -EINVAL;

	pr_debug("Registering compressed device %s\n", device->name);
	if (snd_BUG_ON(!device->ops->open))
		return -EINVAL;
	if (snd_BUG_ON(!device->ops->free))
		return -EINVAL;
	if (snd_BUG_ON(!device->ops->set_params))
		return -EINVAL;
	if (snd_BUG_ON(!device->ops->trigger))
		return -EINVAL;

	mutex_init(&device->lock);

	/* register a compressed card */
	mutex_lock(&device_mutex);
	retval = snd_compress_add_device(device);
	mutex_unlock(&device_mutex);
	return retval;
}