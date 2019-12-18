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
struct hda_pintbl {int member_0; int member_1; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {scalar_t__ power_save_node; struct alc_spec* spec; } ;
struct alc_spec {int /*<<< orphan*/  parse_flags; int /*<<< orphan*/  reboot_notify; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_PINCFG_NO_HP_FIXUP ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,struct hda_pintbl const*) ; 
 int /*<<< orphan*/  snd_hda_gen_reboot_notify ; 

__attribute__((used)) static void alc_fixup_tpt440_dock(struct hda_codec *codec,
				  const struct hda_fixup *fix, int action)
{
	static const struct hda_pintbl pincfgs[] = {
		{ 0x16, 0x21211010 }, /* dock headphone */
		{ 0x19, 0x21a11010 }, /* dock mic */
		{ }
	};
	struct alc_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->reboot_notify = snd_hda_gen_reboot_notify; /* reduce noise */
		spec->parse_flags = HDA_PINCFG_NO_HP_FIXUP;
		codec->power_save_node = 0; /* avoid click noises */
		snd_hda_apply_pincfgs(codec, pincfgs);
	}
}