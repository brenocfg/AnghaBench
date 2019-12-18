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
struct TYPE_2__ {scalar_t__ mfg; scalar_t__ afg; } ;
struct hda_codec {int /*<<< orphan*/  init_pins; TYPE_1__ core; int /*<<< orphan*/  wcaps; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int read_pin_defaults (struct hda_codec*) ; 
 int read_widget_caps (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  snd_array_free (int /*<<< orphan*/ *) ; 
 int snd_hdac_refresh_widgets (TYPE_1__*) ; 

int snd_hda_codec_update_widgets(struct hda_codec *codec)
{
	hda_nid_t fg;
	int err;

	err = snd_hdac_refresh_widgets(&codec->core);
	if (err < 0)
		return err;

	/* Assume the function group node does not change,
	 * only the widget nodes may change.
	 */
	kfree(codec->wcaps);
	fg = codec->core.afg ? codec->core.afg : codec->core.mfg;
	err = read_widget_caps(codec, fg);
	if (err < 0)
		return err;

	snd_array_free(&codec->init_pins);
	err = read_pin_defaults(codec);

	return err;
}