#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_device {struct snd_ac97* device_data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct snd_ac97 {TYPE_3__ dev; int /*<<< orphan*/  num; TYPE_2__* bus; } ;
struct TYPE_6__ {TYPE_1__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ac97_bus_type ; 
 int /*<<< orphan*/  ac97_device_release ; 
 int /*<<< orphan*/  ac97_err (struct snd_ac97*,char*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_ac97_get_short_name (struct snd_ac97*) ; 

__attribute__((used)) static int snd_ac97_dev_register(struct snd_device *device)
{
	struct snd_ac97 *ac97 = device->device_data;
	int err;

	ac97->dev.bus = &ac97_bus_type;
	ac97->dev.parent = ac97->bus->card->dev;
	ac97->dev.release = ac97_device_release;
	dev_set_name(&ac97->dev, "%d-%d:%s",
		     ac97->bus->card->number, ac97->num,
		     snd_ac97_get_short_name(ac97));
	if ((err = device_register(&ac97->dev)) < 0) {
		ac97_err(ac97, "Can't register ac97 bus\n");
		ac97->dev.bus = NULL;
		return err;
	}
	return 0;
}