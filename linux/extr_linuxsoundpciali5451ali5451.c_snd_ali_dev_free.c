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
struct snd_device {struct snd_ali* device_data; } ;
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ali_free (struct snd_ali*) ; 

__attribute__((used)) static int snd_ali_dev_free(struct snd_device *device)
{
	struct snd_ali *codec = device->device_data;
	snd_ali_free(codec);
	return 0;
}