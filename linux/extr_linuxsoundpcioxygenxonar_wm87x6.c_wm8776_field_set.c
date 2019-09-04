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
typedef  unsigned int u8 ;
struct snd_kcontrol {int private_value; struct oxygen* private_data; } ;
struct oxygen {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8776_field_set_from_ctl (struct snd_kcontrol*) ; 

__attribute__((used)) static int wm8776_field_set(struct snd_kcontrol *ctl, unsigned int value)
{
	struct oxygen *chip = ctl->private_data;
	u8 min, max;
	int changed;

	min = (ctl->private_value >> 8) & 0xf;
	max = (ctl->private_value >> 12) & 0xf;
	if (value < min || value > max)
		return -EINVAL;
	mutex_lock(&chip->mutex);
	changed = value != (ctl->private_value & 0xf);
	if (changed) {
		ctl->private_value = (ctl->private_value & ~0xf) | value;
		wm8776_field_set_from_ctl(ctl);
	}
	mutex_unlock(&chip->mutex);
	return changed;
}