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
struct snd_sb_csp {int /*<<< orphan*/  q_lock; scalar_t__ qpos_changed; int /*<<< orphan*/  qsound_space; int /*<<< orphan*/  qsound_switch; TYPE_1__* chip; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;
struct TYPE_2__ {struct snd_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ctl_remove (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_sb_qsound_destroy(struct snd_sb_csp * p)
{
	struct snd_card *card;
	unsigned long flags;

	if (snd_BUG_ON(!p))
		return;

	card = p->chip->card;	
	
	down_write(&card->controls_rwsem);
	if (p->qsound_switch)
		snd_ctl_remove(card, p->qsound_switch);
	if (p->qsound_space)
		snd_ctl_remove(card, p->qsound_space);
	up_write(&card->controls_rwsem);

	/* cancel pending transfer of QSound parameters */
	spin_lock_irqsave (&p->q_lock, flags);
	p->qpos_changed = 0;
	spin_unlock_irqrestore (&p->q_lock, flags);
}