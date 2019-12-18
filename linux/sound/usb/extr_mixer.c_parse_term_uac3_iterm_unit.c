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
struct usb_audio_term {int id; int channels; void* name; scalar_t__ chconfig; void* type; } ;
struct uac3_input_terminal_descriptor {int /*<<< orphan*/  wTerminalDescrStr; int /*<<< orphan*/  wClusterDescrID; int /*<<< orphan*/  wTerminalType; int /*<<< orphan*/  bCSourceID; } ;
struct mixer_build {int dummy; } ;

/* Variables and functions */
 int __check_input_term (struct mixer_build*,int /*<<< orphan*/ ,struct usb_audio_term*) ; 
 int get_cluster_channels_v3 (struct mixer_build*,void*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_term_uac3_iterm_unit(struct mixer_build *state,
				      struct usb_audio_term *term,
				      void *p1, int id)
{
	struct uac3_input_terminal_descriptor *d = p1;
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

	err = get_cluster_channels_v3(state, le16_to_cpu(d->wClusterDescrID));
	if (err < 0)
		return err;
	term->channels = err;

	/* REVISIT: UAC3 IT doesn't have channels cfg */
	term->chconfig = 0;

	term->name = le16_to_cpu(d->wTerminalDescrStr);
	return 0;
}