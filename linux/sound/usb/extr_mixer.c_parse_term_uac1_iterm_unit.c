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
struct usb_audio_term {int /*<<< orphan*/  name; void* chconfig; int /*<<< orphan*/  channels; void* type; } ;
struct uac_input_terminal_descriptor {int /*<<< orphan*/  iTerminal; int /*<<< orphan*/  wChannelConfig; int /*<<< orphan*/  bNrChannels; int /*<<< orphan*/  wTerminalType; } ;
struct mixer_build {int dummy; } ;

/* Variables and functions */
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_term_uac1_iterm_unit(struct mixer_build *state,
				      struct usb_audio_term *term,
				      void *p1, int id)
{
	struct uac_input_terminal_descriptor *d = p1;

	term->type = le16_to_cpu(d->wTerminalType);
	term->channels = d->bNrChannels;
	term->chconfig = le16_to_cpu(d->wChannelConfig);
	term->name = d->iTerminal;
	return 0;
}