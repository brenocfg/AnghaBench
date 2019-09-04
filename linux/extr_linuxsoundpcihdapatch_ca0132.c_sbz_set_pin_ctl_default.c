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
struct hda_codec {int dummy; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sbz_set_pin_ctl_default(struct hda_codec *codec)
{
	hda_nid_t pins[5] = {0x0B, 0x0C, 0x0E, 0x12, 0x13};
	unsigned int i;

	snd_hda_codec_write(codec, 0x11, 0,
			AC_VERB_SET_PIN_WIDGET_CONTROL, 0x40);

	for (i = 0; i < 5; i++)
		snd_hda_codec_write(codec, pins[i], 0,
				AC_VERB_SET_PIN_WIDGET_CONTROL, 0x00);
}