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
struct snd_hwdep {int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  list; int /*<<< orphan*/  dev; int /*<<< orphan*/  device; int /*<<< orphan*/  card; int /*<<< orphan*/  oss_type; scalar_t__ ossreg; int /*<<< orphan*/  open_wait; } ;
struct snd_device {struct snd_hwdep* device_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_hwdep* snd_hwdep_search (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_unregister_oss_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hwdep_dev_disconnect(struct snd_device *device)
{
	struct snd_hwdep *hwdep = device->device_data;

	if (snd_BUG_ON(!hwdep))
		return -ENXIO;
	mutex_lock(&register_mutex);
	if (snd_hwdep_search(hwdep->card, hwdep->device) != hwdep) {
		mutex_unlock(&register_mutex);
		return -EINVAL;
	}
	mutex_lock(&hwdep->open_mutex);
	wake_up(&hwdep->open_wait);
#ifdef CONFIG_SND_OSSEMUL
	if (hwdep->ossreg)
		snd_unregister_oss_device(hwdep->oss_type, hwdep->card, hwdep->device);
#endif
	snd_unregister_device(&hwdep->dev);
	list_del_init(&hwdep->list);
	mutex_unlock(&hwdep->open_mutex);
	mutex_unlock(&register_mutex);
	return 0;
}