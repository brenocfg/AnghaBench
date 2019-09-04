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
struct snd_device {struct cs5535audio* device_data; } ;
struct cs5535audio {int dummy; } ;

/* Variables and functions */
 int snd_cs5535audio_free (struct cs5535audio*) ; 

__attribute__((used)) static int snd_cs5535audio_dev_free(struct snd_device *device)
{
	struct cs5535audio *cs5535au = device->device_data;
	return snd_cs5535audio_free(cs5535au);
}