#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_minor {int type; TYPE_1__* card_ptr; void* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct snd_minor**) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_minor** snd_oss_minors ; 
 int /*<<< orphan*/  sound_oss_mutex ; 

void *snd_lookup_oss_minor_data(unsigned int minor, int type)
{
	struct snd_minor *mreg;
	void *private_data;

	if (minor >= ARRAY_SIZE(snd_oss_minors))
		return NULL;
	mutex_lock(&sound_oss_mutex);
	mreg = snd_oss_minors[minor];
	if (mreg && mreg->type == type) {
		private_data = mreg->private_data;
		if (private_data && mreg->card_ptr)
			get_device(&mreg->card_ptr->card_dev);
	} else
		private_data = NULL;
	mutex_unlock(&sound_oss_mutex);
	return private_data;
}