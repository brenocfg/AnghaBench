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
struct hda_jack_callback {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_gen_hp_automute (struct hda_codec*,struct hda_jack_callback*) ; 

__attribute__((used)) static void alc_update_headset_jack_cb(struct hda_codec *codec,
				       struct hda_jack_callback *jack)
{
	snd_hda_gen_hp_automute(codec, jack);
}