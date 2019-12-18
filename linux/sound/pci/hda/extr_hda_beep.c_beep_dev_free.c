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
struct snd_device {struct hda_beep* device_data; } ;
struct hda_beep {TYPE_1__* codec; } ;
struct TYPE_2__ {int /*<<< orphan*/ * beep; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hda_beep*) ; 

__attribute__((used)) static int beep_dev_free(struct snd_device *device)
{
	struct hda_beep *beep = device->device_data;

	beep->codec->beep = NULL;
	kfree(beep);
	return 0;
}