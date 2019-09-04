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
struct snd_device {struct azx* device_data; } ;
struct TYPE_2__ {int shutdown; } ;
struct azx {TYPE_1__ bus; } ;

/* Variables and functions */

__attribute__((used)) static int hda_tegra_dev_disconnect(struct snd_device *device)
{
	struct azx *chip = device->device_data;

	chip->bus.shutdown = 1;
	return 0;
}