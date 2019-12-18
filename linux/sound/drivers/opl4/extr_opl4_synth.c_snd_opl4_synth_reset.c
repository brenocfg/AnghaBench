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
struct snd_opl4 {int /*<<< orphan*/  chset; int /*<<< orphan*/  off_voices; TYPE_1__* voices; int /*<<< orphan*/  on_voices; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {int number; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPL4_DAMP_BIT ; 
 int OPL4_MAX_VOICES ; 
 scalar_t__ OPL4_REG_MISC ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_midi_channel_set_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_opl4_synth_reset(struct snd_opl4 *opl4)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&opl4->reg_lock, flags);
	for (i = 0; i < OPL4_MAX_VOICES; i++)
		snd_opl4_write(opl4, OPL4_REG_MISC + i, OPL4_DAMP_BIT);
	spin_unlock_irqrestore(&opl4->reg_lock, flags);

	INIT_LIST_HEAD(&opl4->off_voices);
	INIT_LIST_HEAD(&opl4->on_voices);
	memset(opl4->voices, 0, sizeof(opl4->voices));
	for (i = 0; i < OPL4_MAX_VOICES; i++) {
		opl4->voices[i].number = i;
		list_add_tail(&opl4->voices[i].list, &opl4->off_voices);
	}

	snd_midi_channel_set_clear(opl4->chset);
}