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
struct snd_sb_csp {int qpos_left; int qpos_right; int /*<<< orphan*/  qsound_space; int /*<<< orphan*/  qsound_switch; int /*<<< orphan*/  q_lock; scalar_t__ qpos_changed; TYPE_1__* chip; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {struct snd_card* card; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_SB_CSP_QSOUND_MAX_RIGHT ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_sb_csp*) ; 
 int /*<<< orphan*/  snd_sb_qsound_destroy (struct snd_sb_csp*) ; 
 int /*<<< orphan*/  snd_sb_qsound_space ; 
 int /*<<< orphan*/  snd_sb_qsound_switch ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sb_qsound_build(struct snd_sb_csp * p)
{
	struct snd_card *card;
	int err;

	if (snd_BUG_ON(!p))
		return -EINVAL;

	card = p->chip->card;
	p->qpos_left = p->qpos_right = SNDRV_SB_CSP_QSOUND_MAX_RIGHT / 2;
	p->qpos_changed = 0;

	spin_lock_init(&p->q_lock);

	if ((err = snd_ctl_add(card, p->qsound_switch = snd_ctl_new1(&snd_sb_qsound_switch, p))) < 0)
		goto __error;
	if ((err = snd_ctl_add(card, p->qsound_space = snd_ctl_new1(&snd_sb_qsound_space, p))) < 0)
		goto __error;

	return 0;

     __error:
	snd_sb_qsound_destroy(p);
	return err;
}