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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  hp_zephyr_pin_configs ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac92hd83xxx_hp_zephyr_init ; 

__attribute__((used)) static void stac92hd83xxx_fixup_hp_zephyr(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	snd_hda_apply_pincfgs(codec, hp_zephyr_pin_configs);
	snd_hda_add_verbs(codec, stac92hd83xxx_hp_zephyr_init);
}