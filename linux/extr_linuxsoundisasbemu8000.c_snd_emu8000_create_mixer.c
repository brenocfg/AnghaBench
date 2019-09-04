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
struct snd_emu8000 {scalar_t__* controls; int /*<<< orphan*/  control_lock; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMU8000_NUM_CONTROLS ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mixer_defs ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,scalar_t__) ; 
 scalar_t__ snd_ctl_new1 (int /*<<< orphan*/ ,struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_ctl_remove (struct snd_card*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_emu8000_create_mixer(struct snd_card *card, struct snd_emu8000 *emu)
{
	int i, err = 0;

	if (snd_BUG_ON(!emu || !card))
		return -EINVAL;

	spin_lock_init(&emu->control_lock);

	memset(emu->controls, 0, sizeof(emu->controls));
	for (i = 0; i < EMU8000_NUM_CONTROLS; i++) {
		if ((err = snd_ctl_add(card, emu->controls[i] = snd_ctl_new1(mixer_defs[i], emu))) < 0)
			goto __error;
	}
	return 0;

__error:
	for (i = 0; i < EMU8000_NUM_CONTROLS; i++) {
		down_write(&card->controls_rwsem);
		if (emu->controls[i])
			snd_ctl_remove(card, emu->controls[i]);
		up_write(&card->controls_rwsem);
	}
	return err;
}