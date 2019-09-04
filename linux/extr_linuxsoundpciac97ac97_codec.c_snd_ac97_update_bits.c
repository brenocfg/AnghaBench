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
struct snd_ac97 {int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_ac97_update_bits_nolock (struct snd_ac97*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  snd_ac97_valid_reg (struct snd_ac97*,unsigned short) ; 

int snd_ac97_update_bits(struct snd_ac97 *ac97, unsigned short reg, unsigned short mask, unsigned short value)
{
	int change;

	if (!snd_ac97_valid_reg(ac97, reg))
		return -EINVAL;
	mutex_lock(&ac97->reg_mutex);
	change = snd_ac97_update_bits_nolock(ac97, reg, mask, value);
	mutex_unlock(&ac97->reg_mutex);
	return change;
}