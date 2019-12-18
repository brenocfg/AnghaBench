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
struct snd_hwdep {int ossreg; scalar_t__ oss_type; int /*<<< orphan*/  dev; scalar_t__ device; int /*<<< orphan*/  list; struct snd_card* card; } ;
struct snd_device {struct snd_hwdep* device_data; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_HWDEP ; 
 scalar_t__ SNDRV_OSS_DEVICE_TYPE_DMFM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 int /*<<< orphan*/  snd_hwdep_devices ; 
 int /*<<< orphan*/  snd_hwdep_f_ops ; 
 scalar_t__ snd_hwdep_search (struct snd_card*,scalar_t__) ; 
 int snd_register_device (int /*<<< orphan*/ ,struct snd_card*,scalar_t__,int /*<<< orphan*/ *,struct snd_hwdep*,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_register_oss_device (scalar_t__,struct snd_card*,scalar_t__,int /*<<< orphan*/ *,struct snd_hwdep*) ; 

__attribute__((used)) static int snd_hwdep_dev_register(struct snd_device *device)
{
	struct snd_hwdep *hwdep = device->device_data;
	struct snd_card *card = hwdep->card;
	int err;

	mutex_lock(&register_mutex);
	if (snd_hwdep_search(card, hwdep->device)) {
		mutex_unlock(&register_mutex);
		return -EBUSY;
	}
	list_add_tail(&hwdep->list, &snd_hwdep_devices);
	err = snd_register_device(SNDRV_DEVICE_TYPE_HWDEP,
				  hwdep->card, hwdep->device,
				  &snd_hwdep_f_ops, hwdep, &hwdep->dev);
	if (err < 0) {
		dev_err(&hwdep->dev, "unable to register\n");
		list_del(&hwdep->list);
		mutex_unlock(&register_mutex);
		return err;
	}

#ifdef CONFIG_SND_OSSEMUL
	hwdep->ossreg = 0;
	if (hwdep->oss_type >= 0) {
		if (hwdep->oss_type == SNDRV_OSS_DEVICE_TYPE_DMFM &&
		    hwdep->device)
			dev_warn(&hwdep->dev,
				 "only hwdep device 0 can be registered as OSS direct FM device!\n");
		else if (snd_register_oss_device(hwdep->oss_type,
						 card, hwdep->device,
						 &snd_hwdep_f_ops, hwdep) < 0)
			dev_warn(&hwdep->dev,
				 "unable to register OSS compatibility device\n");
		else
			hwdep->ossreg = 1;
	}
#endif
	mutex_unlock(&register_mutex);
	return 0;
}