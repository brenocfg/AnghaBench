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
struct snd_minor {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct snd_minor**) ; 
 int ENOENT ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  kfree (struct snd_minor*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_minor** snd_minors ; 
 int /*<<< orphan*/  sound_mutex ; 

int snd_unregister_device(struct device *dev)
{
	int minor;
	struct snd_minor *preg;

	mutex_lock(&sound_mutex);
	for (minor = 0; minor < ARRAY_SIZE(snd_minors); ++minor) {
		preg = snd_minors[minor];
		if (preg && preg->dev == dev) {
			snd_minors[minor] = NULL;
			device_del(dev);
			kfree(preg);
			break;
		}
	}
	mutex_unlock(&sound_mutex);
	if (minor >= ARRAY_SIZE(snd_minors))
		return -ENOENT;
	return 0;
}