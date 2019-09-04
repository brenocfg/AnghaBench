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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct snd_seq_device {TYPE_1__ dev; } ;
struct snd_device {struct snd_seq_device* device_data; } ;

/* Variables and functions */
 int device_add (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_autoload_drivers () ; 

__attribute__((used)) static int snd_seq_device_dev_register(struct snd_device *device)
{
	struct snd_seq_device *dev = device->device_data;
	int err;

	err = device_add(&dev->dev);
	if (err < 0)
		return err;
	if (!dev->dev.driver)
		queue_autoload_drivers();
	return 0;
}