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
struct usb_mixer_elem_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct usb_mixer_elem_info {size_t val_type; int /*<<< orphan*/  dBmax; int /*<<< orphan*/  dBmin; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  channels; int /*<<< orphan*/  cmask; int /*<<< orphan*/  control; TYPE_1__ head; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 struct usb_mixer_elem_info* mixer_elem_list_to_info (struct usb_mixer_elem_list*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void snd_usb_mixer_dump_cval(struct snd_info_buffer *buffer,
				    struct usb_mixer_elem_list *list)
{
	struct usb_mixer_elem_info *cval = mixer_elem_list_to_info(list);
	static char *val_types[] = {"BOOLEAN", "INV_BOOLEAN",
				    "S8", "U8", "S16", "U16"};
	snd_iprintf(buffer, "    Info: id=%i, control=%i, cmask=0x%x, "
			    "channels=%i, type=\"%s\"\n", cval->head.id,
			    cval->control, cval->cmask, cval->channels,
			    val_types[cval->val_type]);
	snd_iprintf(buffer, "    Volume: min=%i, max=%i, dBmin=%i, dBmax=%i\n",
			    cval->min, cval->max, cval->dBmin, cval->dBmax);
}