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
struct snd_kcontrol_volatile {int access; } ;
struct snd_kcontrol {struct snd_kcontrol_volatile* vd; } ;
struct snd_ctl_elem_id {int dummy; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;

/* Variables and functions */
 int ENOENT ; 
 int SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ctl_build_ioff (struct snd_ctl_elem_id*,struct snd_kcontrol*,unsigned int) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 unsigned int snd_ctl_get_ioff (struct snd_kcontrol*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int snd_ctl_activate_id(struct snd_card *card, struct snd_ctl_elem_id *id,
			int active)
{
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_volatile *vd;
	unsigned int index_offset;
	int ret;

	down_write(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, id);
	if (kctl == NULL) {
		ret = -ENOENT;
		goto unlock;
	}
	index_offset = snd_ctl_get_ioff(kctl, id);
	vd = &kctl->vd[index_offset];
	ret = 0;
	if (active) {
		if (!(vd->access & SNDRV_CTL_ELEM_ACCESS_INACTIVE))
			goto unlock;
		vd->access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	} else {
		if (vd->access & SNDRV_CTL_ELEM_ACCESS_INACTIVE)
			goto unlock;
		vd->access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	}
	snd_ctl_build_ioff(id, kctl, index_offset);
	ret = 1;
 unlock:
	up_write(&card->controls_rwsem);
	if (ret > 0)
		snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_INFO, id);
	return ret;
}