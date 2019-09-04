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
struct usb_mixer_interface {int dummy; } ;
struct usb_mixer_elem_list {int /*<<< orphan*/  kctl; } ;
struct snd_kcontrol_new {int /*<<< orphan*/  private_value; int /*<<< orphan*/  name; int /*<<< orphan*/  info; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int add_single_ctl_with_resume (struct usb_mixer_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_kcontrol_new*,struct usb_mixer_elem_list**) ; 
 int /*<<< orphan*/  snd_ctl_boolean_mono_info ; 
 int /*<<< orphan*/  snd_nativeinstruments_control_get ; 
 int /*<<< orphan*/  snd_nativeinstruments_control_put ; 
 int /*<<< orphan*/  snd_ni_control_init_val (struct usb_mixer_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ni_update_cur_val ; 

__attribute__((used)) static int snd_nativeinstruments_create_mixer(struct usb_mixer_interface *mixer,
					      const struct snd_kcontrol_new *kc,
					      unsigned int count)
{
	int i, err = 0;
	struct snd_kcontrol_new template = {
		.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.get = snd_nativeinstruments_control_get,
		.put = snd_nativeinstruments_control_put,
		.info = snd_ctl_boolean_mono_info,
	};

	for (i = 0; i < count; i++) {
		struct usb_mixer_elem_list *list;

		template.name = kc[i].name;
		template.private_value = kc[i].private_value;

		err = add_single_ctl_with_resume(mixer, 0,
						 snd_ni_update_cur_val,
						 &template, &list);
		if (err < 0)
			break;
		snd_ni_control_init_val(mixer, list->kctl);
	}

	return err;
}