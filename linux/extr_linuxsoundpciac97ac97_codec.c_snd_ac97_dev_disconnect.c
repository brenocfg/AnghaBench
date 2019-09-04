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
struct snd_device {struct snd_ac97* device_data; } ;
struct TYPE_2__ {scalar_t__ bus; } ;
struct snd_ac97 {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 

__attribute__((used)) static int snd_ac97_dev_disconnect(struct snd_device *device)
{
	struct snd_ac97 *ac97 = device->device_data;
	if (ac97->dev.bus)
		device_unregister(&ac97->dev);
	return 0;
}