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
struct hda_pintbl {int member_0; int member_1; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int* preferred_dacs; } ;
struct alc_spec {int /*<<< orphan*/  parse_flags; TYPE_1__ gen; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_CONFIG_DEFAULT_BYTES_3 ; 
 int HDA_FIXUP_ACT_INIT ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_PINCFG_NO_HP_FIXUP ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,struct hda_pintbl const*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_fixup_tpt470_dock(struct hda_codec *codec,
				  const struct hda_fixup *fix, int action)
{
	static const struct hda_pintbl pincfgs[] = {
		{ 0x17, 0x21211010 }, /* dock headphone */
		{ 0x19, 0x21a11010 }, /* dock mic */
		{ }
	};
	/* Assure the speaker pin to be coupled with DAC NID 0x03; otherwise
	 * the speaker output becomes too low by some reason on Thinkpads with
	 * ALC298 codec
	 */
	static hda_nid_t preferred_pairs[] = {
		0x14, 0x03, 0x17, 0x02, 0x21, 0x02,
		0
	};
	struct alc_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gen.preferred_dacs = preferred_pairs;
		spec->parse_flags = HDA_PINCFG_NO_HP_FIXUP;
		snd_hda_apply_pincfgs(codec, pincfgs);
	} else if (action == HDA_FIXUP_ACT_INIT) {
		/* Enable DOCK device */
		snd_hda_codec_write(codec, 0x17, 0,
			    AC_VERB_SET_CONFIG_DEFAULT_BYTES_3, 0);
		/* Enable DOCK device */
		snd_hda_codec_write(codec, 0x19, 0,
			    AC_VERB_SET_CONFIG_DEFAULT_BYTES_3, 0);
	}
}