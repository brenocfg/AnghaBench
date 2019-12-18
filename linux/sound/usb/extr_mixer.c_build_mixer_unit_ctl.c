#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usbmix_name_map {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct usb_mixer_elem_info {int control; int cmask; TYPE_2__ head; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  channels; int /*<<< orphan*/  val_type; } ;
struct usb_audio_term {int dummy; } ;
struct uac_mixer_unit_descriptor {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_1__ id; int /*<<< orphan*/  private_free; } ;
struct mixer_build {int /*<<< orphan*/  chip; TYPE_3__* mixer; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_7__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_MIXER_S16 ; 
 int /*<<< orphan*/  append_ctl_name (struct snd_kcontrol*,char*) ; 
 scalar_t__ check_ignored_ctl (struct usbmix_name_map const*) ; 
 unsigned int check_mapped_name (struct usbmix_name_map const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_matrix_bitmap (int /*<<< orphan*/ *,int,unsigned int,int) ; 
 struct usbmix_name_map* find_map (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_min_max (struct usb_mixer_elem_info*,int /*<<< orphan*/ ) ; 
 unsigned int get_term_name (int /*<<< orphan*/ ,struct usb_audio_term*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct usb_mixer_elem_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct usb_mixer_elem_info*) ; 
 int /*<<< orphan*/  snd_usb_mixer_add_control (TYPE_2__*,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_usb_mixer_elem_free ; 
 int /*<<< orphan*/  snd_usb_mixer_elem_init_std (TYPE_2__*,TYPE_3__*,int) ; 
 unsigned int sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * uac_mixer_unit_bmControls (struct uac_mixer_unit_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_audio_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_audio_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_feature_unit_ctl ; 
 int /*<<< orphan*/  usb_mixer_elem_info_free (struct usb_mixer_elem_info*) ; 

__attribute__((used)) static void build_mixer_unit_ctl(struct mixer_build *state,
				 struct uac_mixer_unit_descriptor *desc,
				 int in_pin, int in_ch, int num_outs,
				 int unitid, struct usb_audio_term *iterm)
{
	struct usb_mixer_elem_info *cval;
	unsigned int i, len;
	struct snd_kcontrol *kctl;
	const struct usbmix_name_map *map;

	map = find_map(state->map, unitid, 0);
	if (check_ignored_ctl(map))
		return;

	cval = kzalloc(sizeof(*cval), GFP_KERNEL);
	if (!cval)
		return;

	snd_usb_mixer_elem_init_std(&cval->head, state->mixer, unitid);
	cval->control = in_ch + 1; /* based on 1 */
	cval->val_type = USB_MIXER_S16;
	for (i = 0; i < num_outs; i++) {
		__u8 *c = uac_mixer_unit_bmControls(desc, state->mixer->protocol);

		if (check_matrix_bitmap(c, in_ch, i, num_outs)) {
			cval->cmask |= (1 << i);
			cval->channels++;
		}
	}

	/* get min/max values */
	get_min_max(cval, 0);

	kctl = snd_ctl_new1(&usb_feature_unit_ctl, cval);
	if (!kctl) {
		usb_audio_err(state->chip, "cannot malloc kcontrol\n");
		usb_mixer_elem_info_free(cval);
		return;
	}
	kctl->private_free = snd_usb_mixer_elem_free;

	len = check_mapped_name(map, kctl->id.name, sizeof(kctl->id.name));
	if (!len)
		len = get_term_name(state->chip, iterm, kctl->id.name,
				    sizeof(kctl->id.name), 0);
	if (!len)
		len = sprintf(kctl->id.name, "Mixer Source %d", in_ch + 1);
	append_ctl_name(kctl, " Volume");

	usb_audio_dbg(state->chip, "[%d] MU [%s] ch = %d, val = %d/%d\n",
		    cval->head.id, kctl->id.name, cval->channels, cval->min, cval->max);
	snd_usb_mixer_add_control(&cval->head, kctl);
}