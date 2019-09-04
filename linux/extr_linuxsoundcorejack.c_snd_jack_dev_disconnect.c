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

/* Variables and functions */

__attribute__((used)) static int snd_jack_dev_disconnect(struct snd_device *device)
{
#ifdef CONFIG_SND_JACK_INPUT_DEV
	struct snd_jack *jack = device->device_data;

	if (!jack->input_dev)
		return 0;

	/* If the input device is registered with the input subsystem
	 * then we need to use a different deallocator. */
	if (jack->registered)
		input_unregister_device(jack->input_dev);
	else
		input_free_device(jack->input_dev);
	jack->input_dev = NULL;
#endif /* CONFIG_SND_JACK_INPUT_DEV */
	return 0;
}