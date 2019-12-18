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
struct snd_kcontrol_volatile {int access; struct snd_ctl_file* owner; } ;
struct snd_kcontrol {int (* put ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;struct snd_kcontrol_volatile* vd; } ;
struct snd_ctl_file {int dummy; } ;
struct snd_ctl_elem_id {int dummy; } ;
struct snd_ctl_elem_value {struct snd_ctl_elem_id id; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int SNDRV_CTL_ELEM_ACCESS_WRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  snd_ctl_build_ioff (struct snd_ctl_elem_id*,struct snd_kcontrol*,unsigned int) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 unsigned int snd_ctl_get_ioff (struct snd_kcontrol*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 
 int stub1 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int snd_ctl_elem_write(struct snd_card *card, struct snd_ctl_file *file,
			      struct snd_ctl_elem_value *control)
{
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_volatile *vd;
	unsigned int index_offset;
	int result;

	kctl = snd_ctl_find_id(card, &control->id);
	if (kctl == NULL)
		return -ENOENT;

	index_offset = snd_ctl_get_ioff(kctl, &control->id);
	vd = &kctl->vd[index_offset];
	if (!(vd->access & SNDRV_CTL_ELEM_ACCESS_WRITE) || kctl->put == NULL ||
	    (file && vd->owner && vd->owner != file)) {
		return -EPERM;
	}

	snd_ctl_build_ioff(&control->id, kctl, index_offset);
	result = kctl->put(kctl, control);
	if (result < 0)
		return result;

	if (result > 0) {
		struct snd_ctl_elem_id id = control->id;
		snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE, &id);
	}

	return 0;
}