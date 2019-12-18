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
struct snd_device {int /*<<< orphan*/  device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_codec_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hda_codec_dev_register(struct snd_device *device)
{
	snd_hda_codec_register(device->device_data);
	return 0;
}