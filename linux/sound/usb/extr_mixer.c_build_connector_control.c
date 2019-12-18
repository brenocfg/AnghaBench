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
struct usb_mixer_interface {scalar_t__ protocol; int /*<<< orphan*/  chip; } ;
struct usb_mixer_elem_info {int channels; int max; int /*<<< orphan*/  head; scalar_t__ min; int /*<<< orphan*/  val_type; int /*<<< orphan*/  control; } ;
struct usb_audio_term {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_free; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UAC2_TE_CONNECTOR ; 
 int /*<<< orphan*/  UAC3_TE_INSERTION ; 
 scalar_t__ UAC_VERSION_2 ; 
 int /*<<< orphan*/  USB_MIXER_BOOLEAN ; 
 int /*<<< orphan*/  get_connector_control_name (struct usb_mixer_interface*,struct usb_audio_term*,int,int /*<<< orphan*/ ,int) ; 
 struct usb_mixer_elem_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct usb_mixer_elem_info*) ; 
 int /*<<< orphan*/  snd_usb_mixer_add_control (int /*<<< orphan*/ *,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_usb_mixer_elem_free ; 
 int /*<<< orphan*/  snd_usb_mixer_elem_init_std (int /*<<< orphan*/ *,struct usb_mixer_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_audio_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_connector_ctl_ro ; 
 int /*<<< orphan*/  usb_mixer_elem_info_free (struct usb_mixer_elem_info*) ; 

__attribute__((used)) static void build_connector_control(struct usb_mixer_interface *mixer,
				    struct usb_audio_term *term, bool is_input)
{
	struct snd_kcontrol *kctl;
	struct usb_mixer_elem_info *cval;

	cval = kzalloc(sizeof(*cval), GFP_KERNEL);
	if (!cval)
		return;
	snd_usb_mixer_elem_init_std(&cval->head, mixer, term->id);
	/*
	 * UAC2: The first byte from reading the UAC2_TE_CONNECTOR control returns the
	 * number of channels connected.
	 *
	 * UAC3: The first byte specifies size of bitmap for the inserted controls. The
	 * following byte(s) specifies which connectors are inserted.
	 *
	 * This boolean ctl will simply report if any channels are connected
	 * or not.
	 */
	if (mixer->protocol == UAC_VERSION_2)
		cval->control = UAC2_TE_CONNECTOR;
	else /* UAC_VERSION_3 */
		cval->control = UAC3_TE_INSERTION;

	cval->val_type = USB_MIXER_BOOLEAN;
	cval->channels = 1; /* report true if any channel is connected */
	cval->min = 0;
	cval->max = 1;
	kctl = snd_ctl_new1(&usb_connector_ctl_ro, cval);
	if (!kctl) {
		usb_audio_err(mixer->chip, "cannot malloc kcontrol\n");
		usb_mixer_elem_info_free(cval);
		return;
	}
	get_connector_control_name(mixer, term, is_input, kctl->id.name,
				   sizeof(kctl->id.name));
	kctl->private_free = snd_usb_mixer_elem_free;
	snd_usb_mixer_add_control(&cval->head, kctl);
}