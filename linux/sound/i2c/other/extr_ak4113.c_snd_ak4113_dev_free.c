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
struct snd_device {struct ak4113* device_data; } ;
struct ak4113 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ak4113_free (struct ak4113*) ; 

__attribute__((used)) static int snd_ak4113_dev_free(struct snd_device *device)
{
	struct ak4113 *chip = device->device_data;
	snd_ak4113_free(chip);
	return 0;
}