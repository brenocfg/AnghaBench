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
struct snd_ctl_elem_id {scalar_t__ numid; int /*<<< orphan*/  index; } ;
struct snd_kcontrol {unsigned int count; struct snd_ctl_elem_id id; int /*<<< orphan*/  list; int /*<<< orphan*/  info; } ;
struct snd_card {unsigned int controls_count; int /*<<< orphan*/  controls_rwsem; scalar_t__ last_numid; int /*<<< orphan*/  controls; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_ADD ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_ctl_find_hole (struct snd_card*,unsigned int) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  snd_ctl_free_one (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 
 int snd_ctl_remove (struct snd_card*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int snd_ctl_replace(struct snd_card *card, struct snd_kcontrol *kcontrol,
		    bool add_on_replace)
{
	struct snd_ctl_elem_id id;
	unsigned int count;
	unsigned int idx;
	struct snd_kcontrol *old;
	int ret;

	if (!kcontrol)
		return -EINVAL;
	if (snd_BUG_ON(!card || !kcontrol->info)) {
		ret = -EINVAL;
		goto error;
	}
	id = kcontrol->id;
	down_write(&card->controls_rwsem);
	old = snd_ctl_find_id(card, &id);
	if (!old) {
		if (add_on_replace)
			goto add;
		up_write(&card->controls_rwsem);
		ret = -EINVAL;
		goto error;
	}
	ret = snd_ctl_remove(card, old);
	if (ret < 0) {
		up_write(&card->controls_rwsem);
		goto error;
	}
add:
	if (snd_ctl_find_hole(card, kcontrol->count) < 0) {
		up_write(&card->controls_rwsem);
		ret = -ENOMEM;
		goto error;
	}
	list_add_tail(&kcontrol->list, &card->controls);
	card->controls_count += kcontrol->count;
	kcontrol->id.numid = card->last_numid + 1;
	card->last_numid += kcontrol->count;
	id = kcontrol->id;
	count = kcontrol->count;
	up_write(&card->controls_rwsem);
	for (idx = 0; idx < count; idx++, id.index++, id.numid++)
		snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_ADD, &id);
	return 0;

error:
	snd_ctl_free_one(kcontrol);
	return ret;
}