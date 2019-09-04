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
struct cmipci {int* opened; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  reg_lock; TYPE_1__* channel; } ;
struct TYPE_2__ {int is_dac; int /*<<< orphan*/ * substream; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ENDBDAC ; 
 int CM_OPEN_CH_MASK ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cmipci_ch_reset (struct cmipci*,int) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_device_check(struct cmipci *cm, int mode)
{
	int ch = mode & CM_OPEN_CH_MASK;

	mutex_lock(&cm->open_mutex);
	if (cm->opened[ch] == mode) {
		if (cm->channel[ch].substream) {
			snd_cmipci_ch_reset(cm, ch);
			cm->channel[ch].running = 0;
			cm->channel[ch].substream = NULL;
		}
		cm->opened[ch] = 0;
		if (! cm->channel[ch].is_dac) {
			/* enable dual DAC mode again */
			cm->channel[ch].is_dac = 1;
			spin_lock_irq(&cm->reg_lock);
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_ENDBDAC);
			spin_unlock_irq(&cm->reg_lock);
		}
	}
	mutex_unlock(&cm->open_mutex);
}