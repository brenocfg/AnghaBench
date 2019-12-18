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
struct snd_timer_instance {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  register_mutex ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_timer_close_locked (struct snd_timer_instance*,struct device**) ; 

int snd_timer_close(struct snd_timer_instance *timeri)
{
	struct device *card_dev_to_put = NULL;
	int err;

	if (snd_BUG_ON(!timeri))
		return -ENXIO;

	mutex_lock(&register_mutex);
	err = snd_timer_close_locked(timeri, &card_dev_to_put);
	mutex_unlock(&register_mutex);
	/* put_device() is called after unlock for avoiding deadlock */
	if (card_dev_to_put)
		put_device(card_dev_to_put);
	return err;
}