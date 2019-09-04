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
typedef  int /*<<< orphan*/  usb_mixer_elem_resume_func_t ;
struct usb_mixer_interface {int dummy; } ;
struct usb_mixer_elem_list {int id; int /*<<< orphan*/  resume; struct usb_mixer_interface* mixer; } ;
struct snd_kcontrol_new {int dummy; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_free; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct usb_mixer_elem_list*) ; 
 struct usb_mixer_elem_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new const*,struct usb_mixer_elem_list*) ; 
 int snd_usb_mixer_add_control (struct usb_mixer_elem_list*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_usb_mixer_elem_free ; 

__attribute__((used)) static int add_single_ctl_with_resume(struct usb_mixer_interface *mixer,
				      int id,
				      usb_mixer_elem_resume_func_t resume,
				      const struct snd_kcontrol_new *knew,
				      struct usb_mixer_elem_list **listp)
{
	struct usb_mixer_elem_list *list;
	struct snd_kcontrol *kctl;

	list = kzalloc(sizeof(*list), GFP_KERNEL);
	if (!list)
		return -ENOMEM;
	if (listp)
		*listp = list;
	list->mixer = mixer;
	list->id = id;
	list->resume = resume;
	kctl = snd_ctl_new1(knew, list);
	if (!kctl) {
		kfree(list);
		return -ENOMEM;
	}
	kctl->private_free = snd_usb_mixer_elem_free;
	return snd_usb_mixer_add_control(list, kctl);
}