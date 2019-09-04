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

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_timer_close_locked (struct snd_timer_instance*) ; 

int snd_timer_close(struct snd_timer_instance *timeri)
{
	int err;

	if (snd_BUG_ON(!timeri))
		return -ENXIO;

	mutex_lock(&register_mutex);
	err = snd_timer_close_locked(timeri);
	mutex_unlock(&register_mutex);
	return err;
}