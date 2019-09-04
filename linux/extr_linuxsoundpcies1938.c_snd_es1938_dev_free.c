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
struct snd_device {struct es1938* device_data; } ;
struct es1938 {int dummy; } ;

/* Variables and functions */
 int snd_es1938_free (struct es1938*) ; 

__attribute__((used)) static int snd_es1938_dev_free(struct snd_device *device)
{
	struct es1938 *chip = device->device_data;
	return snd_es1938_free(chip);
}