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
struct usb_mixer_interface {int /*<<< orphan*/  chip; } ;
struct usb_audio_term {int dummy; } ;

/* Variables and functions */
 int get_term_name (int /*<<< orphan*/ ,struct usb_audio_term*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void get_connector_control_name(struct usb_mixer_interface *mixer,
				       struct usb_audio_term *term,
				       bool is_input, char *name, int name_size)
{
	int name_len = get_term_name(mixer->chip, term, name, name_size, 0);

	if (name_len == 0)
		strlcpy(name, "Unknown", name_size);

	/*
	 *  sound/core/ctljack.c has a convention of naming jack controls
	 * by ending in " Jack".  Make it slightly more useful by
	 * indicating Input or Output after the terminal name.
	 */
	if (is_input)
		strlcat(name, " - Input Jack", name_size);
	else
		strlcat(name, " - Output Jack", name_size);
}