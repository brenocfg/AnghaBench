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
struct snd_device {struct ensoniq* device_data; } ;
struct ensoniq {int dummy; } ;

/* Variables and functions */
 int snd_ensoniq_free (struct ensoniq*) ; 

__attribute__((used)) static int snd_ensoniq_dev_free(struct snd_device *device)
{
	struct ensoniq *ensoniq = device->device_data;
	return snd_ensoniq_free(ensoniq);
}