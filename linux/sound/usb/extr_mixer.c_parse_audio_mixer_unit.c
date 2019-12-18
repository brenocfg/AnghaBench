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
struct usb_audio_term {scalar_t__ channels; } ;
struct uac_mixer_unit_descriptor {int bNrInPins; int /*<<< orphan*/ * baSourceID; } ;
struct mixer_build {TYPE_1__* mixer; int /*<<< orphan*/  chip; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_mixer_unit_ctl (struct mixer_build*,struct uac_mixer_unit_descriptor*,int,int,int,int,struct usb_audio_term*) ; 
 int check_input_term (struct mixer_build*,int /*<<< orphan*/ ,struct usb_audio_term*) ; 
 scalar_t__ check_matrix_bitmap (int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ mixer_bitmap_overflow (struct uac_mixer_unit_descriptor*,int /*<<< orphan*/ ,int,int) ; 
 int parse_audio_unit (struct mixer_build*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uac_mixer_unit_bmControls (struct uac_mixer_unit_descriptor*,int /*<<< orphan*/ ) ; 
 int uac_mixer_unit_get_channels (struct mixer_build*,struct uac_mixer_unit_descriptor*) ; 
 int /*<<< orphan*/  usb_audio_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int parse_audio_mixer_unit(struct mixer_build *state, int unitid,
				  void *raw_desc)
{
	struct uac_mixer_unit_descriptor *desc = raw_desc;
	struct usb_audio_term iterm;
	int input_pins, num_ins, num_outs;
	int pin, ich, err;

	err = uac_mixer_unit_get_channels(state, desc);
	if (err < 0) {
		usb_audio_err(state->chip,
			      "invalid MIXER UNIT descriptor %d\n",
			      unitid);
		return err;
	}

	num_outs = err;
	input_pins = desc->bNrInPins;

	num_ins = 0;
	ich = 0;
	for (pin = 0; pin < input_pins; pin++) {
		err = parse_audio_unit(state, desc->baSourceID[pin]);
		if (err < 0)
			continue;
		/* no bmControls field (e.g. Maya44) -> ignore */
		if (!num_outs)
			continue;
		err = check_input_term(state, desc->baSourceID[pin], &iterm);
		if (err < 0)
			return err;
		num_ins += iterm.channels;
		if (mixer_bitmap_overflow(desc, state->mixer->protocol,
					  num_ins, num_outs))
			break;
		for (; ich < num_ins; ich++) {
			int och, ich_has_controls = 0;

			for (och = 0; och < num_outs; och++) {
				__u8 *c = uac_mixer_unit_bmControls(desc,
						state->mixer->protocol);

				if (check_matrix_bitmap(c, ich, och, num_outs)) {
					ich_has_controls = 1;
					break;
				}
			}
			if (ich_has_controls)
				build_mixer_unit_ctl(state, desc, pin, ich, num_outs,
						     unitid, &iterm);
		}
	}
	return 0;
}