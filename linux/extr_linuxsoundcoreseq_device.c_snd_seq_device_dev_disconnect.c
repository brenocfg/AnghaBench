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
struct snd_seq_device {int /*<<< orphan*/  dev; } ;
struct snd_device {struct snd_seq_device* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_seq_device_dev_disconnect(struct snd_device *device)
{
	struct snd_seq_device *dev = device->device_data;

	device_del(&dev->dev);
	return 0;
}