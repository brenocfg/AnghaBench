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
struct snd_es1688 {unsigned char trigger_value; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int SNDRV_PCM_TRIGGER_STOP ; 
 int snd_es1688_read (struct snd_es1688*,int) ; 
 int /*<<< orphan*/  snd_es1688_write (struct snd_es1688*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_es1688_trigger(struct snd_es1688 *chip, int cmd, unsigned char value)
{
	int val;

	if (cmd == SNDRV_PCM_TRIGGER_STOP) {
		value = 0x00;
	} else if (cmd != SNDRV_PCM_TRIGGER_START) {
		return -EINVAL;
	}
	spin_lock(&chip->reg_lock);
	chip->trigger_value = value;
	val = snd_es1688_read(chip, 0xb8);
	if ((val < 0) || (val & 0x0f) == value) {
		spin_unlock(&chip->reg_lock);
		return -EINVAL;	/* something is wrong */
	}
#if 0
	printk(KERN_DEBUG "trigger: val = 0x%x, value = 0x%x\n", val, value);
	printk(KERN_DEBUG "trigger: pointer = 0x%x\n",
	       snd_dma_pointer(chip->dma8, chip->dma_size));
#endif
	snd_es1688_write(chip, 0xb8, (val & 0xf0) | value);
	spin_unlock(&chip->reg_lock);
	return 0;
}