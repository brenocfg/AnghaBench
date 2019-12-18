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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  eapds; int /*<<< orphan*/  num_eapds; int /*<<< orphan*/  dynamic_eapd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_FIXUP_ACT_INIT ; 
 int /*<<< orphan*/  cx_auto_turn_eapd (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 

__attribute__((used)) static int cx_auto_init(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	snd_hda_gen_init(codec);
	if (!spec->dynamic_eapd)
		cx_auto_turn_eapd(codec, spec->num_eapds, spec->eapds, true);

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_INIT);

	return 0;
}