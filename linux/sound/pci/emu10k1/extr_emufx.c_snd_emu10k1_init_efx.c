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
struct TYPE_2__ {int /*<<< orphan*/  gpr_ctl; int /*<<< orphan*/  irq_lock; } ;
struct snd_emu10k1 {scalar_t__ audigy; TYPE_1__ fx8010; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int _snd_emu10k1_audigy_init_efx (struct snd_emu10k1*) ; 
 int _snd_emu10k1_init_efx (struct snd_emu10k1*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int snd_emu10k1_init_efx(struct snd_emu10k1 *emu)
{
	spin_lock_init(&emu->fx8010.irq_lock);
	INIT_LIST_HEAD(&emu->fx8010.gpr_ctl);
	if (emu->audigy)
		return _snd_emu10k1_audigy_init_efx(emu);
	else
		return _snd_emu10k1_init_efx(emu);
}