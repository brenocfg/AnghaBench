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
struct snd_device {struct hda_beep* device_data; } ;
struct hda_beep {int registered; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int input_register_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beep_dev_register(struct snd_device *device)
{
	struct hda_beep *beep = device->device_data;
	int err;

	err = input_register_device(beep->dev);
	if (!err)
		beep->registered = true;
	return err;
}