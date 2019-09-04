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
struct snd_device {struct snd_card* device_data; } ;
struct snd_card {int /*<<< orphan*/  ctl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_CONTROL ; 
 int /*<<< orphan*/  snd_ctl_f_ops ; 
 int snd_register_device (int /*<<< orphan*/ ,struct snd_card*,int,int /*<<< orphan*/ *,struct snd_card*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ctl_dev_register(struct snd_device *device)
{
	struct snd_card *card = device->device_data;

	return snd_register_device(SNDRV_DEVICE_TYPE_CONTROL, card, -1,
				   &snd_ctl_f_ops, card, &card->ctl_dev);
}