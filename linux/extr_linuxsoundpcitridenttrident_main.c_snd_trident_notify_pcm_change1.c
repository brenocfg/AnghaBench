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
struct snd_kcontrol {TYPE_1__* vd; } ;
struct snd_ctl_elem_id {int dummy; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int SNDRV_CTL_EVENT_MASK_INFO ; 
 int SNDRV_CTL_EVENT_MASK_VALUE ; 
 int /*<<< orphan*/  snd_ctl_build_ioff (struct snd_ctl_elem_id*,struct snd_kcontrol*,int) ; 
 int /*<<< orphan*/  snd_ctl_notify (struct snd_card*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_trident_notify_pcm_change1(struct snd_card *card,
					   struct snd_kcontrol *kctl,
					   int num, int activate)
{
	struct snd_ctl_elem_id id;

	if (! kctl)
		return;
	if (activate)
		kctl->vd[num].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	else
		kctl->vd[num].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO,
		       snd_ctl_build_ioff(&id, kctl, num));
}