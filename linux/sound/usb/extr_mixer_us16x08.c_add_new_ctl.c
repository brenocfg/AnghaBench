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
struct usb_mixer_interface {int /*<<< orphan*/  chip; } ;
struct TYPE_4__ {int id; int /*<<< orphan*/ * resume; struct usb_mixer_interface* mixer; } ;
struct usb_mixer_elem_info {int val_type; int channels; TYPE_2__ head; void* private_data; scalar_t__ idx_off; scalar_t__ control; } ;
struct snd_kcontrol_new {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; int /*<<< orphan*/  private_free; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  elem_private_free ; 
 int /*<<< orphan*/  kfree (struct usb_mixer_elem_info*) ; 
 struct usb_mixer_elem_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new const*,struct usb_mixer_elem_info*) ; 
 int snd_usb_mixer_add_control (TYPE_2__*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_usb_mixer_elem_free ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  usb_audio_dbg (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int add_new_ctl(struct usb_mixer_interface *mixer,
	const struct snd_kcontrol_new *ncontrol,
	int index, int val_type, int channels,
	const char *name, void *opt,
	bool do_private_free,
	struct usb_mixer_elem_info **elem_ret)
{
	struct snd_kcontrol *kctl;
	struct usb_mixer_elem_info *elem;
	int err;

	usb_audio_dbg(mixer->chip, "us16x08 add mixer %s\n", name);

	elem = kzalloc(sizeof(*elem), GFP_KERNEL);
	if (!elem)
		return -ENOMEM;

	elem->head.mixer = mixer;
	elem->head.resume = NULL;
	elem->control = 0;
	elem->idx_off = 0;
	elem->head.id = index;
	elem->val_type = val_type;
	elem->channels = channels;
	elem->private_data = opt;

	kctl = snd_ctl_new1(ncontrol, elem);
	if (!kctl) {
		kfree(elem);
		return -ENOMEM;
	}

	if (do_private_free)
		kctl->private_free = elem_private_free;
	else
		kctl->private_free = snd_usb_mixer_elem_free;

	strlcpy(kctl->id.name, name, sizeof(kctl->id.name));

	err = snd_usb_mixer_add_control(&elem->head, kctl);
	if (err < 0)
		return err;

	if (elem_ret)
		*elem_ret = elem;

	return 0;
}