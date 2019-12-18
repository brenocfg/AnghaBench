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
struct usb_audio_term {int type; int id; int /*<<< orphan*/  name; int /*<<< orphan*/  chconfig; int /*<<< orphan*/  channels; } ;
struct uac_processing_unit_descriptor {int /*<<< orphan*/ * baSourceID; scalar_t__ bNrInPins; } ;
struct mixer_build {TYPE_1__* mixer; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 int UAC_VERSION_3 ; 
 int __check_input_term (struct mixer_build*,int /*<<< orphan*/ ,struct usb_audio_term*) ; 
 int /*<<< orphan*/  uac_processing_unit_bNrChannels (struct uac_processing_unit_descriptor*) ; 
 int /*<<< orphan*/  uac_processing_unit_iProcessing (struct uac_processing_unit_descriptor*,int) ; 
 int /*<<< orphan*/  uac_processing_unit_wChannelConfig (struct uac_processing_unit_descriptor*,int) ; 

__attribute__((used)) static int parse_term_proc_unit(struct mixer_build *state,
				struct usb_audio_term *term,
				void *p1, int id, int vtype)
{
	struct uac_processing_unit_descriptor *d = p1;
	int protocol = state->mixer->protocol;
	int err;

	if (d->bNrInPins) {
		/* call recursively to retrieve the channel info */
		err = __check_input_term(state, d->baSourceID[0], term);
		if (err < 0)
			return err;
	}

	term->type = vtype << 16; /* virtual type */
	term->id = id;

	if (protocol == UAC_VERSION_3)
		return 0;

	if (!term->channels) {
		term->channels = uac_processing_unit_bNrChannels(d);
		term->chconfig = uac_processing_unit_wChannelConfig(d, protocol);
	}
	term->name = uac_processing_unit_iProcessing(d, protocol);
	return 0;
}