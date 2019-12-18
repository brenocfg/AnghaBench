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
struct hda_codec {int /*<<< orphan*/  core; struct hda_bus* bus; } ;
struct hda_bus {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ snd_hda_lock_devices (struct hda_bus*) ; 
 int /*<<< orphan*/  snd_hda_unlock_devices (struct hda_bus*) ; 
 int /*<<< orphan*/  snd_hdac_device_unregister (int /*<<< orphan*/ *) ; 

int snd_hda_codec_reset(struct hda_codec *codec)
{
	struct hda_bus *bus = codec->bus;

	if (snd_hda_lock_devices(bus) < 0)
		return -EBUSY;

	/* OK, let it free */
	snd_hdac_device_unregister(&codec->core);

	/* allow device access again */
	snd_hda_unlock_devices(bus);
	return 0;
}