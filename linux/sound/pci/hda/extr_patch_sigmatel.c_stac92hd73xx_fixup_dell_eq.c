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
struct sigmatel_spec {int volknob_init; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  dell_eq_core_init ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac92hd73xx_fixup_dell (struct hda_codec*) ; 

__attribute__((used)) static void stac92hd73xx_fixup_dell_eq(struct hda_codec *codec,
				       const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	stac92hd73xx_fixup_dell(codec);
	snd_hda_add_verbs(codec, dell_eq_core_init);
	spec->volknob_init = 1;
}