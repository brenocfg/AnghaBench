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
struct usb_audio_term {int id; int /*<<< orphan*/  name; int /*<<< orphan*/  chconfig; int /*<<< orphan*/  channels; int /*<<< orphan*/  type; } ;
struct uac2_input_terminal_descriptor {int /*<<< orphan*/  iTerminal; int /*<<< orphan*/  bmChannelConfig; int /*<<< orphan*/  bNrChannels; int /*<<< orphan*/  wTerminalType; int /*<<< orphan*/  bCSourceID; } ;
struct mixer_build {int dummy; } ;

/* Variables and functions */
 int __check_input_term (struct mixer_build*,int /*<<< orphan*/ ,struct usb_audio_term*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_term_uac2_iterm_unit(struct mixer_build *state,
				      struct usb_audio_term *term,
				      void *p1, int id)
{
	struct uac2_input_terminal_descriptor *d = p1;
	int err;

	/* call recursively to verify the referenced clock entity */
	err = __check_input_term(state, d->bCSourceID, term);
	if (err < 0)
		return err;

	/* save input term properties after recursion,
	 * to ensure they are not overriden by the recursion calls
	 */
	term->id = id;
	term->type = le16_to_cpu(d->wTerminalType);
	term->channels = d->bNrChannels;
	term->chconfig = le32_to_cpu(d->bmChannelConfig);
	term->name = d->iTerminal;
	return 0;
}