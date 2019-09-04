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
struct snd_wm8776 {struct snd_card* card; } ;
struct snd_kcontrol_volatile {int /*<<< orphan*/  access; } ;
struct snd_kcontrol {int /*<<< orphan*/  id; struct snd_kcontrol_volatile* vd; } ;
struct snd_ctl_elem_id {int /*<<< orphan*/  iface; int /*<<< orphan*/  name; } ;
struct snd_card {int dummy; } ;
typedef  int /*<<< orphan*/  elem_id ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 unsigned int snd_ctl_get_ioff (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void snd_wm8776_activate_ctl(struct snd_wm8776 *wm,
				    const char *ctl_name,
				    bool active)
{
	struct snd_card *card = wm->card;
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_volatile *vd;
	struct snd_ctl_elem_id elem_id;
	unsigned int index_offset;

	memset(&elem_id, 0, sizeof(elem_id));
	strlcpy(elem_id.name, ctl_name, sizeof(elem_id.name));
	elem_id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	kctl = snd_ctl_find_id(card, &elem_id);
	if (!kctl)
		return;
	index_offset = snd_ctl_get_ioff(kctl, &kctl->id);
	vd = &kctl->vd[index_offset];
	if (active)
		vd->access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	else
		vd->access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_INFO, &kctl->id);
}