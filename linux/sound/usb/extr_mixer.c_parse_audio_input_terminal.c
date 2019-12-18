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
struct usb_audio_term {int dummy; } ;
struct uac3_input_terminal_descriptor {unsigned int bTerminalID; int /*<<< orphan*/  bmControls; } ;
struct uac2_input_terminal_descriptor {unsigned int bTerminalID; int /*<<< orphan*/  bmControls; } ;
struct mixer_build {TYPE_1__* mixer; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 unsigned int UAC2_TE_CONNECTOR ; 
 unsigned int UAC3_TE_INSERTION ; 
 scalar_t__ UAC_VERSION_2 ; 
 scalar_t__ UAC_VERSION_3 ; 
 int /*<<< orphan*/  build_connector_control (TYPE_1__*,struct usb_audio_term*,int) ; 
 int /*<<< orphan*/  check_input_term (struct mixer_build*,unsigned int,struct usb_audio_term*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ uac_v2v3_control_is_readable (unsigned int,unsigned int) ; 

__attribute__((used)) static int parse_audio_input_terminal(struct mixer_build *state, int unitid,
				      void *raw_desc)
{
	struct usb_audio_term iterm;
	unsigned int control, bmctls, term_id;

	if (state->mixer->protocol == UAC_VERSION_2) {
		struct uac2_input_terminal_descriptor *d_v2 = raw_desc;
		control = UAC2_TE_CONNECTOR;
		term_id = d_v2->bTerminalID;
		bmctls = le16_to_cpu(d_v2->bmControls);
	} else if (state->mixer->protocol == UAC_VERSION_3) {
		struct uac3_input_terminal_descriptor *d_v3 = raw_desc;
		control = UAC3_TE_INSERTION;
		term_id = d_v3->bTerminalID;
		bmctls = le32_to_cpu(d_v3->bmControls);
	} else {
		return 0; /* UAC1. No Insertion control */
	}

	check_input_term(state, term_id, &iterm);

	/* Check for jack detection. */
	if (uac_v2v3_control_is_readable(bmctls, control))
		build_connector_control(state->mixer, &iterm, true);

	return 0;
}