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
struct snd_es1688 {int dummy; } ;
struct snd_device {struct snd_es1688* device_data; } ;

/* Variables and functions */
 int snd_es1688_free (struct snd_es1688*) ; 

__attribute__((used)) static int snd_es1688_dev_free(struct snd_device *device)
{
	struct snd_es1688 *chip = device->device_data;
	return snd_es1688_free(chip);
}