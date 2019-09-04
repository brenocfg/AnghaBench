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
struct snd_device {struct fm801* device_data; } ;
struct fm801 {int dummy; } ;

/* Variables and functions */
 int snd_fm801_free (struct fm801*) ; 

__attribute__((used)) static int snd_fm801_dev_free(struct snd_device *device)
{
	struct fm801 *chip = device->device_data;
	return snd_fm801_free(chip);
}