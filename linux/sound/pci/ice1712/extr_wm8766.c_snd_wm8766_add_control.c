#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_wm8766 {int /*<<< orphan*/  card; TYPE_2__* ctl; } ;
struct TYPE_3__ {int /*<<< orphan*/ * p; } ;
struct snd_kcontrol_new {int private_value; int /*<<< orphan*/  info; TYPE_1__ tlv; int /*<<< orphan*/  access; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {int dummy; } ;
typedef  int /*<<< orphan*/  cont ;
struct TYPE_4__ {int flags; int type; int max; struct snd_kcontrol* kctl; int /*<<< orphan*/ * tlv; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
#define  SNDRV_CTL_ELEM_TYPE_BOOLEAN 130 
#define  SNDRV_CTL_ELEM_TYPE_ENUMERATED 129 
#define  SNDRV_CTL_ELEM_TYPE_INTEGER 128 
 int WM8766_FLAG_ALC ; 
 int WM8766_FLAG_LIM ; 
 int WM8766_FLAG_STEREO ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_ctl_boolean_mono_info ; 
 int /*<<< orphan*/  snd_ctl_boolean_stereo_info ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_wm8766*) ; 
 int /*<<< orphan*/  snd_wm8766_ctl_get ; 
 int /*<<< orphan*/  snd_wm8766_ctl_put ; 
 int /*<<< orphan*/  snd_wm8766_enum_info ; 
 int /*<<< orphan*/  snd_wm8766_volume_info ; 

__attribute__((used)) static int snd_wm8766_add_control(struct snd_wm8766 *wm, int num)
{
	struct snd_kcontrol_new cont;
	struct snd_kcontrol *ctl;

	memset(&cont, 0, sizeof(cont));
	cont.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	cont.private_value = num;
	cont.name = wm->ctl[num].name;
	cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	if (wm->ctl[num].flags & WM8766_FLAG_LIM ||
	    wm->ctl[num].flags & WM8766_FLAG_ALC)
		cont.access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	cont.tlv.p = NULL;
	cont.get = snd_wm8766_ctl_get;
	cont.put = snd_wm8766_ctl_put;

	switch (wm->ctl[num].type) {
	case SNDRV_CTL_ELEM_TYPE_INTEGER:
		cont.info = snd_wm8766_volume_info;
		cont.access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		cont.tlv.p = wm->ctl[num].tlv;
		break;
	case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
		wm->ctl[num].max = 1;
		if (wm->ctl[num].flags & WM8766_FLAG_STEREO)
			cont.info = snd_ctl_boolean_stereo_info;
		else
			cont.info = snd_ctl_boolean_mono_info;
		break;
	case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		cont.info = snd_wm8766_enum_info;
		break;
	default:
		return -EINVAL;
	}
	ctl = snd_ctl_new1(&cont, wm);
	if (!ctl)
		return -ENOMEM;
	wm->ctl[num].kctl = ctl;

	return snd_ctl_add(wm->card, ctl);
}