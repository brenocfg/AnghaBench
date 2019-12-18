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
typedef  int /*<<< orphan*/  template ;
struct snd_kcontrol_new {unsigned long private_value; int /*<<< orphan*/  access; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_free; } ;
struct sigmadsp_control {struct snd_kcontrol* kcontrol; int /*<<< orphan*/  samplerates; int /*<<< orphan*/  name; } ;
struct sigmadsp {TYPE_2__* component; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  memset (struct snd_kcontrol_new*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigmadsp_control_free ; 
 int /*<<< orphan*/  sigmadsp_ctrl_get ; 
 int /*<<< orphan*/  sigmadsp_ctrl_info ; 
 int /*<<< orphan*/  sigmadsp_ctrl_put ; 
 int /*<<< orphan*/  sigmadsp_samplerate_valid (int /*<<< orphan*/ ,unsigned int) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct sigmadsp*) ; 

__attribute__((used)) static int sigmadsp_alloc_control(struct sigmadsp *sigmadsp,
	struct sigmadsp_control *ctrl, unsigned int samplerate_mask)
{
	struct snd_kcontrol_new template;
	struct snd_kcontrol *kcontrol;

	memset(&template, 0, sizeof(template));
	template.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	template.name = ctrl->name;
	template.info = sigmadsp_ctrl_info;
	template.get = sigmadsp_ctrl_get;
	template.put = sigmadsp_ctrl_put;
	template.private_value = (unsigned long)ctrl;
	template.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	if (!sigmadsp_samplerate_valid(ctrl->samplerates, samplerate_mask))
		template.access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;

	kcontrol = snd_ctl_new1(&template, sigmadsp);
	if (!kcontrol)
		return -ENOMEM;

	kcontrol->private_free = sigmadsp_control_free;
	ctrl->kcontrol = kcontrol;

	return snd_ctl_add(sigmadsp->component->card->snd_card, kcontrol);
}