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
struct snd_i2c_device {int /*<<< orphan*/  (* private_free ) (struct snd_i2c_device*) ;int /*<<< orphan*/  list; scalar_t__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_i2c_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_i2c_device*) ; 

int snd_i2c_device_free(struct snd_i2c_device *device)
{
	if (device->bus)
		list_del(&device->list);
	if (device->private_free)
		device->private_free(device);
	kfree(device);
	return 0;
}