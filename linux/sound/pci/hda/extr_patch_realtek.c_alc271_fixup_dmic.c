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
struct hda_verb {int member_0; int member_2; int /*<<< orphan*/  member_1; } ;
struct hda_fixup {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip_name; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ AC_JACK_PORT_FIXED ; 
#define  AC_VERB_SET_COEF_INDEX 129 
#define  AC_VERB_SET_PROC_COEF 128 
 scalar_t__ get_defcfg_connect (unsigned int) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,struct hda_verb const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void alc271_fixup_dmic(struct hda_codec *codec,
			      const struct hda_fixup *fix, int action)
{
	static const struct hda_verb verbs[] = {
		{0x20, AC_VERB_SET_COEF_INDEX, 0x0d},
		{0x20, AC_VERB_SET_PROC_COEF, 0x4000},
		{}
	};
	unsigned int cfg;

	if (strcmp(codec->core.chip_name, "ALC271X") &&
	    strcmp(codec->core.chip_name, "ALC269VB"))
		return;
	cfg = snd_hda_codec_get_pincfg(codec, 0x12);
	if (get_defcfg_connect(cfg) == AC_JACK_PORT_FIXED)
		snd_hda_sequence_write(codec, verbs);
}