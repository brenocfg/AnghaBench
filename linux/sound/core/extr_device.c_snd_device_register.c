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
struct snd_device {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int __snd_device_register (struct snd_device*) ; 
 struct snd_device* look_for_dev (struct snd_card*,void*) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 scalar_t__ snd_BUG_ON (int) ; 

int snd_device_register(struct snd_card *card, void *device_data)
{
	struct snd_device *dev;

	if (snd_BUG_ON(!card || !device_data))
		return -ENXIO;
	dev = look_for_dev(card, device_data);
	if (dev)
		return __snd_device_register(dev);
	snd_BUG();
	return -ENXIO;
}