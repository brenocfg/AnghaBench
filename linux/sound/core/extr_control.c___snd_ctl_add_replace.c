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
struct snd_ctl_elem_id {scalar_t__ index; scalar_t__ numid; int /*<<< orphan*/  name; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  device; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {unsigned int count; struct snd_ctl_elem_id id; int /*<<< orphan*/  list; } ;
struct snd_card {unsigned int controls_count; scalar_t__ last_numid; int /*<<< orphan*/  controls; int /*<<< orphan*/  dev; } ;
typedef  enum snd_ctl_add_mode { ____Placeholder_snd_ctl_add_mode } snd_ctl_add_mode ;

/* Variables and functions */
 int CTL_ADD_EXCLUSIVE ; 
 int CTL_REPLACE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_ADD ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_ctl_find_hole (struct snd_card*,unsigned int) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 
 int snd_ctl_remove (struct snd_card*,struct snd_kcontrol*) ; 

__attribute__((used)) static int __snd_ctl_add_replace(struct snd_card *card,
				 struct snd_kcontrol *kcontrol,
				 enum snd_ctl_add_mode mode)
{
	struct snd_ctl_elem_id id;
	unsigned int idx;
	unsigned int count;
	struct snd_kcontrol *old;
	int err;

	id = kcontrol->id;
	if (id.index > UINT_MAX - kcontrol->count)
		return -EINVAL;

	old = snd_ctl_find_id(card, &id);
	if (!old) {
		if (mode == CTL_REPLACE)
			return -EINVAL;
	} else {
		if (mode == CTL_ADD_EXCLUSIVE) {
			dev_err(card->dev,
				"control %i:%i:%i:%s:%i is already present\n",
				id.iface, id.device, id.subdevice, id.name,
				id.index);
			return -EBUSY;
		}

		err = snd_ctl_remove(card, old);
		if (err < 0)
			return err;
	}

	if (snd_ctl_find_hole(card, kcontrol->count) < 0)
		return -ENOMEM;

	list_add_tail(&kcontrol->list, &card->controls);
	card->controls_count += kcontrol->count;
	kcontrol->id.numid = card->last_numid + 1;
	card->last_numid += kcontrol->count;

	id = kcontrol->id;
	count = kcontrol->count;
	for (idx = 0; idx < count; idx++, id.index++, id.numid++)
		snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_ADD, &id);

	return 0;
}