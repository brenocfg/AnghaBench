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
struct hda_beep {int /*<<< orphan*/  dev; scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turn_off_beep (struct hda_beep*) ; 

__attribute__((used)) static int beep_dev_disconnect(struct snd_device *device)
{
	struct hda_beep *beep = device->device_data;

	if (beep->registered)
		input_unregister_device(beep->dev);
	else
		input_free_device(beep->dev);
	turn_off_beep(beep);
	return 0;
}