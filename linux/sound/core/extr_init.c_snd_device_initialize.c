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
struct snd_card {int /*<<< orphan*/  card_dev; } ;
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/  class; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_release ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  sound_class ; 

void snd_device_initialize(struct device *dev, struct snd_card *card)
{
	device_initialize(dev);
	if (card)
		dev->parent = &card->card_dev;
	dev->class = sound_class;
	dev->release = default_release;
}