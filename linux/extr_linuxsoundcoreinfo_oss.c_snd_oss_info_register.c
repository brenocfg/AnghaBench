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

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNDRV_CARDS ; 
 int SNDRV_OSS_INFO_DEV_COUNT ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 char*** snd_sndstat_strings ; 
 int /*<<< orphan*/  strings ; 

int snd_oss_info_register(int dev, int num, char *string)
{
	char *x;

	if (snd_BUG_ON(dev < 0 || dev >= SNDRV_OSS_INFO_DEV_COUNT))
		return -ENXIO;
	if (snd_BUG_ON(num < 0 || num >= SNDRV_CARDS))
		return -ENXIO;
	mutex_lock(&strings);
	if (string == NULL) {
		if ((x = snd_sndstat_strings[num][dev]) != NULL) {
			kfree(x);
			x = NULL;
		}
	} else {
		x = kstrdup(string, GFP_KERNEL);
		if (x == NULL) {
			mutex_unlock(&strings);
			return -ENOMEM;
		}
	}
	snd_sndstat_strings[num][dev] = x;
	mutex_unlock(&strings);
	return 0;
}